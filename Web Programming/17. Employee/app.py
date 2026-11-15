import sqlite3
from flask import Flask, render_template, request, redirect, url_for

app = Flask(__name__)
DB_NAME = "employees.db"

def get_db_connection():
    conn = sqlite3.connect(DB_NAME)
    conn.row_factory = sqlite3.Row
    return conn

def init_db():
    conn = get_db_connection()
    conn.execute("""
        CREATE TABLE IF NOT EXISTS employees (
            emp_id INTEGER PRIMARY KEY AUTOINCREMENT,
            name TEXT NOT NULL,
            department TEXT NOT NULL,
            designation TEXT NOT NULL,
            email TEXT UNIQUE NOT NULL,
            salary REAL NOT NULL
        )
    """)
    conn.commit()
    conn.close()

@app.route("/")
def index():
    query = request.args.get("search", "").strip()
    conn = get_db_connection()

    if query:
        if query.isdigit():
            employees = conn.execute(
                "SELECT * FROM employees WHERE emp_id = ? OR name LIKE ?",
                (int(query), f"%{query}%")
            ).fetchall()
        else:
            employees = conn.execute(
                "SELECT * FROM employees WHERE name LIKE ? OR department LIKE ?",
                (f"%{query}%", f"%{query}%")
            ).fetchall()
    else:
        employees = conn.execute("SELECT * FROM employees").fetchall()

    conn.close()
    return render_template("index.html", employees=employees, query=query)

@app.route("/add", methods=["GET", "POST"])
def add_employee():
    if request.method == "POST":
        name = request.form.get("name", "").strip()
        department = request.form.get("department", "").strip()
        designation = request.form.get("designation", "").strip()
        email = request.form.get("email", "").strip()
        salary_str = request.form.get("salary", "").strip()

        if not name or not department or not designation or not email or not salary_str:
            return render_template("add.html", error="All fields are required.")

        try:
            salary = float(salary_str)
            if salary <= 0:
                return render_template("add.html", error="Salary must be a positive number.")
        except ValueError:
            return render_template("add.html", error="Please enter a valid salary amount.")

        try:
            conn = get_db_connection()
            conn.execute(
                "INSERT INTO employees (name, department, designation, email, salary) VALUES (?, ?, ?, ?, ?)",
                (name, department, designation, email, salary)
            )
            conn.commit()
            conn.close()
            return redirect(url_for("index"))
        except sqlite3.IntegrityError:
            return render_template("add.html", error="Employee email already exists.")

    return render_template("add.html")

@app.route("/edit/<int:emp_id>", methods=["GET", "POST"])
def edit_employee(emp_id):
    conn = get_db_connection()
    if request.method == "POST":
        name = request.form.get("name", "").strip()
        department = request.form.get("department", "").strip()
        designation = request.form.get("designation", "").strip()
        email = request.form.get("email", "").strip()
        salary_str = request.form.get("salary", "").strip()

        if not name or not department or not designation or not email or not salary_str:
            conn.close()
            return render_template("edit.html", error="All fields are required.", employee={"emp_id": emp_id, "name": name, "department": department, "designation": designation, "email": email, "salary": salary_str})

        try:
            salary = float(salary_str)
            if salary <= 0:
                conn.close()
                return render_template("edit.html", error="Salary must be a positive number.", employee={"emp_id": emp_id, "name": name, "department": department, "designation": designation, "email": email, "salary": salary_str})
        except ValueError:
            conn.close()
            return render_template("edit.html", error="Please enter a valid salary amount.", employee={"emp_id": emp_id, "name": name, "department": department, "designation": designation, "email": email, "salary": salary_str})

        try:
            conn.execute(
                "UPDATE employees SET name = ?, department = ?, designation = ?, email = ?, salary = ? WHERE emp_id = ?",
                (name, department, designation, email, salary, emp_id)
            )
            conn.commit()
            conn.close()
            return redirect(url_for("index"))
        except sqlite3.IntegrityError:
            conn.close()
            return render_template("edit.html", error="Employee email already exists.", employee={"emp_id": emp_id, "name": name, "department": department, "designation": designation, "email": email, "salary": salary_str})

    employee = conn.execute("SELECT * FROM employees WHERE emp_id = ?", (emp_id,)).fetchone()
    conn.close()
    return render_template("edit.html", employee=employee)

@app.route("/delete/<int:emp_id>", methods=["POST"])
def delete_employee(emp_id):
    conn = get_db_connection()
    conn.execute("DELETE FROM employees WHERE emp_id = ?", (emp_id,))
    conn.commit()
    conn.close()
    return redirect(url_for("index"))

if __name__ == "__main__":
    init_db()
    app.run(debug=True)


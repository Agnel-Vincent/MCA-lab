import sqlite3
from flask import Flask, render_template, request, redirect, url_for

app = Flask(__name__)
DB_NAME = "records.db"

def get_db_connection():
    conn = sqlite3.connect(DB_NAME)
    conn.row_factory = sqlite3.Row
    return conn

def init_db():
    conn = get_db_connection()
    conn.execute("""
        CREATE TABLE IF NOT EXISTS items (
            id INTEGER PRIMARY KEY AUTOINCREMENT,
            title TEXT NOT NULL,
            description TEXT NOT NULL
        )
    """)
    conn.commit()
    conn.close()

@app.route("/")
def index():
    conn = get_db_connection()
    records = conn.execute("SELECT id, title, description FROM items").fetchall()
    conn.close()
    return render_template("index.html", records=records)

@app.route("/create", methods=["GET", "POST"])
def create_record():
    if request.method == "POST":
        title = request.form.get("title", "").strip()
        description = request.form.get("description", "").strip()

        if not title or not description:
            return render_template("create.html", error="All fields are required.")

        conn = get_db_connection()
        conn.execute("INSERT INTO items (title, description) VALUES (?, ?)", (title, description))
        conn.commit()
        conn.close()
        return redirect(url_for("index"))

    return render_template("create.html")

@app.route("/update/<int:id>", methods=["GET", "POST"])
def update_record(id):
    conn = get_db_connection()
    if request.method == "POST":
        title = request.form.get("title", "").strip()
        description = request.form.get("description", "").strip()

        if not title or not description:
            conn.close()
            return render_template("update.html", error="All fields are required.", record={"id": id, "title": title, "description": description})

        conn.execute("UPDATE items SET title = ?, description = ? WHERE id = ?", (title, description, id))
        conn.commit()
        conn.close()
        return redirect(url_for("index"))

    record = conn.execute("SELECT id, title, description FROM items WHERE id = ?", (id,)).fetchone()
    conn.close()
    return render_template("update.html", record=record)

@app.route("/delete/<int:id>", methods=["POST"])
def delete_record(id):
    conn = get_db_connection()
    conn.execute("DELETE FROM items WHERE id = ?", (id,))
    conn.commit()
    conn.close()
    return redirect(url_for("index"))

if __name__ == "__main__":
    init_db()
    app.run(debug=True)


/**
 * CHRONO 01 // Interactive Logic
 * Simple, vanilla JavaScript for client-side form validation and interactive state.
 * Easy to explain during lab viva/evaluations.
 */

document.addEventListener('DOMContentLoaded', function () {
    const orderForm = document.getElementById('orderForm');
    const orderSuccess = document.getElementById('orderSuccess');
    const customerEmail = document.getElementById('customerEmail');
    const userEmailPlaceholder = document.getElementById('userEmailPlaceholder');
    const resetOrderBtn = document.getElementById('resetOrderBtn');

    // 1. Handle Form Submission
    if (orderForm) {
        orderForm.addEventListener('submit', function (event) {
            // Prevent standard page reload to demonstrate single-page state handling
            event.preventDefault();

            const email = customerEmail.value.trim();

            if (email) {
                // Populate placeholder with submitted email
                userEmailPlaceholder.textContent = email;

                // Hide the form and reveal the confirmation card
                orderForm.style.display = 'none';
                orderSuccess.style.display = 'block';

                // Optional smooth scroll to ensure confirmation is in view
                orderSuccess.scrollIntoView({ behavior: 'smooth', block: 'nearest' });
            }
        });
    }

    // 2. Handle Reset / "Submit Another Order"
    if (resetOrderBtn) {
        resetOrderBtn.addEventListener('click', function () {
            // Reset the form fields
            orderForm.reset();

            // Toggle visibility back to input state
            orderSuccess.style.display = 'none';
            orderForm.style.display = 'block';
        });
    }
});

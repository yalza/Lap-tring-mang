const signUpForm = document.querySelector("form");

signUpForm.addEventListener("submit", (event) => {
  event.preventDefault();

  const formData = new FormData(signUpForm);
  const data = Object.fromEntries(formData.entries());

  fetch("http://localhost:3000/signup", {
    method: "POST",
    headers: {
      "Content-Type": "application/json",
    },
    body: JSON.stringify(data),
  })
    .then((response) => {
      if (response.status === 201) {
        window.location.href = "login.html";
      } else if (response.status === 409) {
        window.alert("Username already exists.");
      } else if (response.status === 422) {
        window.alert("Passwords do not match.");
      } else if (response.status === 400) {
        window.alert("Cannot be null");
      }
    })
    .catch((error) => console.error(error));
});

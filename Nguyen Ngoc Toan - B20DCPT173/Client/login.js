const loginForm = document.getElementById("login-form");

loginForm.addEventListener("submit", (event) => {
  event.preventDefault();

  const formData = new FormData(loginForm);

  const data = {};
  for (const [key, value] of formData.entries()) {
    data[key] = value;
  }

  fetch("http://localhost:3000/login", {
    method: "POST",
    headers: {
      "Content-Type": "application/json",
      Origin: "http://localhost:5500",
      Credentials: "include",
    },
    body: JSON.stringify(data),
  })
    .then((response) => {
      if (response.status === 200) {
        // Lấy thông tin cookie từ header
        const cookies = response.headers.get("Set-Cookie");
        // Lưu cookie vào localStorage để sử dụng sau này
        localStorage.setItem("myCookie", cookies);

        // Set cookie với giá trị là data
        document.cookie = `data=${JSON.stringify(data)};path=/`;

        window.location.href = "home.html";
      } else if (response.status === 401) {
        window.location.href = "signup.html";
      }
    })
    .catch((error) => console.error(error));
});

function fillUserInfo() {
  const usernameInput = document.getElementById("username-input");
  const passwordInput = document.getElementById("password-input");
  const fullnameInput = document.getElementById("fullname-input");
  const dateofbirthInput = document.getElementById("dateofbirth-input");
  const hometownInput = document.getElementById("hometown-input");

  // Lấy thông tin từ server và điền vào form
  fetch("http://localhost:3000/profile")
    .then((response) => response.json())
    .then((data) => {
      document.getElementById("username").innerText = data.username;
      if (data.username) usernameInput.value = data.username;
      if (data.password) passwordInput.value = data.password;
      if (data.fullname) fullnameInput.value = data.fullname;
      if (data.dateofbirth) dateofbirthInput.value = data.dateofbirth;
      if (data.hometown) hometownInput.value = data.hometown;
    })
    .catch((error) => console.error(error));
}

fillUserInfo(); // Gọi hàm fillUserInfo() khi trang được load

///////////////////////////////

const saveButton = document.getElementById("save-button");

saveButton.addEventListener("click", () => {
  const username = document.getElementById("username-input").value;
  const password = document.getElementById("password-input").value;
  const fullname = document.getElementById("fullname-input").value;
  const dateofbirth = document.getElementById("dateofbirth-input").value;
  const hometown = document.getElementById("hometown-input").value;

  fetch("http://localhost:3000/profile", {
    method: "POST",
    headers: {
      "Content-Type": "application/json",
    },
    body: JSON.stringify({
      username,
      password,
      fullname,
      dateofbirth,
      hometown,
    }),
  })
    .then((response) => {})
    .then(() => {
      fetch("http://localhost:3000/profile", {
        method: "GET",
        headers: {
          "Content-Type": "application/json",
        },
      })
        .then((response) => {
          return response.json();
        })
        .then((data) => {
          window.location.href = "profile.html";
          window.alert("Sửa thông tin thành công");
        });
    })
    .catch((error) => {
      console.error(error);
    });
});

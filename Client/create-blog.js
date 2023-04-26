fetch("http://localhost:3000/create-blog", {
  method: "GET",
  headers: {
    "Content-Type": "application/json",
  },
})
  .then((response) => response.json())
  .then((data) => {
    // Handle success
    document.getElementById("username").innerText = data.username;
  })
  .catch((error) => {
    // Handle error
  });

const form = document.getElementById("create-blog-form");

form.addEventListener("submit", (event) => {
  event.preventDefault();

  const title = document.getElementById("title").value;
  const content = document.getElementById("content").value;

  fetch("http://localhost:3000/create-blog", {
    method: "POST",
    headers: {
      "Content-Type": "application/json",
    },
    body: JSON.stringify({
      title,
      content,
    }),
  })
    .then((response) => {
      return response.json();
    })
    .then((data) => {
      console.log(data);
      localStorage.setItem("blogId", JSON.stringify(data._id));
      window.location.href = "blog-detail.html";
      // Handle success
    })
    .catch((error) => {
      // Handle error
    });
});

const blogData = JSON.parse(localStorage.getItem("blogUpdate"));
console.log(blogData);
document.getElementById("title").value = blogData.titleBlog;
document.getElementById("content").value = blogData.contentBlog;
document.getElementById("username").innerText = blogData.username;

document.getElementById("updateBtn").addEventListener("click", () => {
  fetch(`http://localhost:3000/update-blog/${blogData._id}`, {
    method: "POST",
    headers: {
      "Content-Type": "application/json",
    },
    body: JSON.stringify({
      title: document.getElementById("title").value,
      content: document.getElementById("content").value,
    }),
  })
    .then((response) => {
      return response.json();
    })
    .then((data) => {
      localStorage.setItem("blogId", JSON.stringify(blogData._id));
      window.location.href = "blog-detail.html";
    })
    .catch((error) => {
      console.error(error);
    });
});

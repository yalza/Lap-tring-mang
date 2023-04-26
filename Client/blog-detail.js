const blogId = JSON.parse(localStorage.getItem("blogId"));

fetch(`http://localhost:3000/blog-detail/${blogId}`)
  .then((response) => {
    return response.json();
  })
  .then((data) => {
    // Đổ dữ liệu lên trang
    document.getElementById("username").innerText = data.username;
    const blogTitle = document.getElementById("blog-title");
    const blogContent = document.getElementById("blog-content");
    const blogAuthor = document.getElementById("blog-author");
    const blogDate = document.getElementById("blog-date");

    blogTitle.innerText = data.titleBlog;
    blogContent.innerText = data.content;
    blogAuthor.innerText = "Author: " + data.author;
    blogDate.innerText = "Date: " + data.date;

    // Đổ dữ liệu comment lên trang
    const commentList = document.getElementById("comment-list");

    data.comments.forEach((comment) => {
      const commentItem = document.createElement("div");
      commentItem.classList.add("comment__item");

      const authorSpan = document.createElement("span");
      authorSpan.style.fontWeight = "bold";
      authorSpan.style.fontSize = "20px";
      authorSpan.style.marginRight = "1rem";
      authorSpan.innerText = comment.author;

      const dateSpan = document.createElement("span");
      dateSpan.style.opacity = "0.7";
      dateSpan.innerText = comment.date;

      const commentP = document.createElement("p");
      commentP.innerText = comment.comment;

      commentItem.appendChild(authorSpan);
      commentItem.appendChild(dateSpan);
      commentItem.appendChild(commentP);

      if (comment.author === data.authorBlog) {
        const deleteLink = document.createElement("a");
        deleteLink.href = "/delete-comment/" + comment._id;

        const deleteButton = document.createElement("button");
        deleteButton.type = "button";
        deleteButton.classList.add("btn-delete");
        deleteButton.innerText = "Xóa";

        deleteLink.appendChild(deleteButton);
        commentItem.appendChild(deleteLink);
      }

      const updateLink = document.createElement("a");
      updateLink.href = "";

      const updateButton = document.createElement("button");
      updateButton.type = "button";
      updateButton.classList.add("btn-update");
      updateButton.innerText = "Sửa";

      updateLink.appendChild(updateButton);
      commentItem.appendChild(updateLink);

      commentList.appendChild(commentItem);
    });
  })
  .catch((err) => console.log(err));

//  comment

const commentForm = document.getElementById("comment-form");

commentForm.addEventListener("submit", (event) => {
  event.preventDefault();

  // Lấy giá trị của input comment
  const commentInput = document.getElementById("comment-input");
  const comment = commentInput.value;

  // Tạo object chứa các giá trị của comment
  const commentData = {
    comment: comment,
  };

  // Gửi request đến server
  fetch(`http://localhost:3000/blog-detail/${blogId}`, {
    method: "POST",
    headers: {
      "Content-Type": "application/json",
    },
    body: JSON.stringify(commentData),
  })
    .then((response) => {
      window.location.href = "blog-detail.html";
      return response.json();
    })
    .then((data) => {
      // Thực hiện các hành động sau khi nhận được response từ server
    })
    .catch((error) => {
      // Xử lý lỗi khi gửi request đến server
      console.error(error);
    });
});

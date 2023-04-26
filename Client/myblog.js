fetch("http://localhost:3000/myblog")
  .then((response) => {
    return response.json();
  })
  .then((data) => {
    document.getElementById("username").innerText = data.username;
    const cardList = document.getElementById("card-list");
    data.blogs.forEach((blog) => {
      const card = document.createElement("div");
      card.className = "card";
      const link = document.createElement("a");
      link.addEventListener("click", (event) => {
        localStorage.setItem("blogId", JSON.stringify(blog._id));
        event.preventDefault();
        window.location.href = "blog-detail.html";
      });
      const title = document.createElement("h2");
      title.className = "card-title";
      title.innerText = blog.title;
      link.appendChild(title);
      card.appendChild(link);
      const author = document.createElement("p");
      author.className = "card-author";
      author.innerText = `Tác giả: ${blog.author}`;
      card.appendChild(author);
      const date = document.createElement("p");
      date.className = "card-date";
      date.innerText = `Ngày tạo: ${blog.date}`;
      card.appendChild(date);
      const btnDel = document.createElement("button");
      btnDel.className = "btn-del";
      btnDel.innerText = "Xóa";
      card.appendChild(btnDel);
      btnDel.addEventListener("click", () => {
        const confirmed = confirm("Bạn có chắc muốn xóa blog này không?");
        if (confirmed) {
          fetch(`http://localhost:3000/delete-blog/${blog._id}`, {
            method: "GET",
          })
            .then((response) => {})
            .then((result) => {
              window.location.reload();
            })
            .catch((error) => {
              console.error(error);
              alert("Có lỗi xảy ra khi xóa blog!");
            });
        }
      });
      const btnUpd = document.createElement("button");
      btnUpd.className = "btn-upd";
      btnUpd.innerText = "Sửa";
      btnUpd.addEventListener("click", () => {
        fetch(`http://localhost:3000/update-blog/${blog._id}`, {
          method: "GET",
        })
          .then((response) => {
            return response.json();
          })
          .then((result) => {
            localStorage.setItem("blogUpdate", JSON.stringify(result));
            window.location.href = "update-blog.html";
          })
          .catch((error) => {
            console.error(error);
            alert("Có lỗi xảy ra khi xóa blog!");
          });
      });
      card.appendChild(btnUpd);
      cardList.appendChild(card);
    });
  })
  .catch((error) => console.log(error));

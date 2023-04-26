fetch("http://localhost:3000/home")
  .then((response) => {
    return response.json();
  })
  .then(async (data) => {
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
      cardList.appendChild(card);
    });
  })
  .catch((error) => console.log(error));

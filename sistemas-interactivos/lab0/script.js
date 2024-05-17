const wishlist = {
  items: [],

  element: document.querySelector("#wishlist"),

  clear() {
    this.element.querySelectorAll('li').forEach((li) => {
      this.element.removeChild(li);
    });
  },

  render() {
    this.clear();

    this.items.forEach((i) => {
      const li = document.createElement('li');
      const remove = document.createElement('button');
      remove.innerHTML = '-';
      remove.addEventListener('click', (e) => {
        this.remove(i.id);
      });
      li.innerHTML = i.name;
      li.appendChild(remove);

      this.element.appendChild(li);
    });
  },

  contains: function(itemId) {
    return this.items.findIndex((item) => item.id === itemId) >= 0;
  },

  add: function(item) {
    if (!this.contains(item.id)) {
      this.items.push(item);
      this.render();
    }
  },

  remove: function(itemId) {
    const idx = this.items.findIndex((i) => itemId === i.id)
    this.items.splice(idx, 1);
    this.render();
  }
};


document.querySelectorAll('.add-to-whislist').forEach((e) => {
  e.addEventListener('click', (ev) => {
    const element = ev.target;
    wishlist.add({
      id: element.dataset.id,
      name: element.dataset.name
    });
  })
});
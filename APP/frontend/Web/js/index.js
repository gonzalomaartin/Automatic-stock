var swiper = new Swiper('.mySwiper-1', {
    slidesPerView: 1,
    spaceBetween: 30,
    loop: true,
    pagination: {
        el: '.swiper-pagination',
        clickable: true,
    },
    navigation: {
        nextEl: '.swiper-button-next',
        prevEl: '.swiper-button-prev',
    },

});

var swiper = new Swiper('.mySwiper-2', {
    slidesPerView: 1,
    spaceBetween: 30,
    loop: true,
    pagination: {
        el: '.swiper-pagination',
        clickable: true,
    },
    navigation: {
        nextEl: '.swiper-button-next',
        prevEl: '.swiper-button-prev',
    },
    breakpoints: {
        0: {    
            slidesPerView: 1,
        },
        520: {  
            slidesPerView: 2,
        },
        950: {
            slidesPerView: 3,
        },
    }

});

var swiper = new Swiper('.mySwiper-3', {
    slidesPerView: 1,
    spaceBetween: 30,
    loop: true,
    pagination: {
        el: '.swiper-pagination',
        clickable: true,
    },
    navigation: {
        nextEl: '.swiper-button-next',
        prevEl: '.swiper-button-prev',
    },
    breakpoints: {
        0: {    
            slidesPerView: 1,
        },
        520: {  
            slidesPerView: 2,
        },
        950: {
            slidesPerView: 3,
        },
    }

});

const containerProducts = document.getElementById('cont-products');

function showProductsList(productos) {
    productos.forEach(producto => {
        const newProduct = document.createElement("div");
        newProduct.classList.add('swiper-slide');
        newProduct.innerHTML = `
            <div class="product">
                <img src="${producto.img}" alt=""> 
                <div class="product-txt">
                    <h3>${producto.title}</h3>
                    <p>${producto.size} cm</p>
                    <p class="price">${producto.price}€</p>
                    <button class="btn-add-cart" data-id="${producto.id}">Agregar al carrito</button>
                </div>
            </div>
            `
        containerProducts.appendChild(newProduct);
        newProduct.getElementsByTagName("button")[0].addEventListener('click', () => addCart(producto)) });
}

showProductsList(products);

function hideNavBar(){
    const navListItems = document.querySelectorAll(".navbar li");
    const navBar = document.querySelector(".navbar");

    navListItems.forEach((item) => {
        item.addEventListener('click', () => {
            navBar.style.opacity = "0";
            setTimeout(() => {
                navBar.style.display = "none";
            }, 500); 
        });
    });
}

function showNavBar(){
    const navBar = document.querySelector(".navbar");
    const menuIcon = document.querySelector("#menu");
        menuIcon.addEventListener('click', () => {
            if(navBar.style.display === "block"){
                navBar.style.opacity = "0";
                setTimeout(() => {
                    navBar.style.display = "none";
                }, 500); 
                return;
            }
            else{
                navBar.style.display = "block";
                setTimeout(() => {
                    navBar.style.opacity = "0.9";
                }, 100); 
            }
        });
}
showNavBar();
hideNavBar();

function addCart(producto){
    const memory = JSON.parse(localStorage.getItem("products"));
    let cuenta = 0;
    if(!memory){
        const newProduct = getNewProductForMemory(producto);
        localStorage.setItem("products", JSON.stringify([newProduct]));
        cuenta = 1;
    } 
     else {
        const indexproduct = memory.findIndex(product => product.id === producto.id);
        const newMemory = memory;
        if(indexproduct === -1)
        {
            newMemory.push(getNewProductForMemory(producto));
            cuenta = 1; 
        }
        else
        {
            newMemory[indexproduct].quantity++;
            cuenta = newMemory[indexproduct].quantity;
        }
        localStorage.setItem("products", JSON.stringify(newMemory));
    }
    updateNumberCart();
    return cuenta;
}

function substractCart(producto){
    const memory = JSON.parse(localStorage.getItem("products"));
    const indexproduct = memory.findIndex(product => product.id === producto.id);
    if(memory[indexproduct].quantity === 1){
       memory.splice(indexproduct, 1);
    } else {
        memory[indexproduct].quantity--;
    }
    localStorage.setItem("products", JSON.stringify(memory));
    updateNumberCart();
}

// Añadir cantidad de producto
function getNewProductForMemory(producto){
    const newProduct = producto;
    newProduct.quantity = 1;
    return newProduct;
}

const countCart = document.querySelector('.cart-count');
function updateNumberCart(){
    const memory = JSON.parse(localStorage.getItem("products"));
    if(memory && memory.length > 0){
        const elementsQuantity = memory.reduce((acc, current) => acc + current.quantity, 0);
        countCart.innerText = elementsQuantity;
        return elementsQuantity;
    }else{
        countCart.innerText = 0;
    }
}

updateNumberCart();
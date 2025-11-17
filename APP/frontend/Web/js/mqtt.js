const url = "wss://broker.emqx.io:8084/mqtt"
var client = mqtt.connect(url);

const carritoElement = document.getElementById("confirmar-compra");

async function PublicarPedido() {
    client.on('connect', function () {
        carritoElement.addEventListener('click',() => {
            const productos = JSON.parse(localStorage.getItem("products"));
            for (let i = 0; i < productos.length; i++) {
                delete productos[i].img;
                delete productos[i].price;
                delete productos[i].title;
                delete productos[i].size;
            }
            if(productos && productos.length > 0){
                client.subscribe('giirob/pr2/B1/infopedido', function (err) {
                    if (!err) {
                        client.publish('giirob/pr2/B1/infopedido', JSON.stringify(productos), function(err) {
                            if(err) {
                                window.location.href = "fallo_conexion.html";
                            }
                        });
                    } 
                    else{
                        window.location.href = "fallo_conexion.html";                    
                    }
                });
            }
            else{
                console.log("No hay productos en el carrito");
            }
        });
    });
}

async function ejecutarFunciones() {
    await PublicarPedido();
    carritoElement.addEventListener('click', () => {
        setTimeout(VaciarCarrito, 2000);
    });
}

ejecutarFunciones();



    


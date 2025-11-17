console.clear();

import database from '../database.js';
import express from 'express';
import morgan from 'morgan';
import cors from 'cors';

//Configuración inicial
const app = express();
app.set('port', 4000);
app.listen(app.get('port'));
console.log("escuchando en el puerto "+ app.get('port'));

//middlewares
app.use(cors({
    origin: ["http://127.0.0.1:5501", "http://127.0.0.1:5500"]
}));
app.use(morgan('dev'));
app.use(express.json());

//Rutas
app.get("/pedido", async (req, res) => {
    const connection = database;
    const result = await connection.query("SELECT * FROM pedido");
    res.json(result);
});

app.post("/pedido", async (req, res) => {
    if(req.body && req.body.length > 0){
        let TotalPrice = 0;
        let cajas_s = 0;
        let cajas_m = 0;
        let cajas_l = 0;
        let cajas_xl = 0;
        req.body.forEach(producto => {
            for(let i = 0; i < producto.length; i++){
                TotalPrice += parseInt(producto[i].price);
                if(producto[i].title == "BOX S"){
                    cajas_s = parseInt(producto[i].quantity);
                } else if(producto[i].title == "BOX M"){
                    cajas_m = parseInt(producto[i].quantity);
                } else if(producto[i].title == "BOX L"){
                    cajas_l = parseInt(producto[i].quantity);
                } else if(producto[i].title == "BOX XL"){
                    cajas_xl = parseInt(producto[i].quantity);
                }
            }
        });
        const consultaPedido = {
            text: "INSERT INTO pedido (cajas_s, cajas_m, cajas_l, cajas_xl, precio_total) VALUES ($1, $2, $3, $4, $5) RETURNING id_pedido",
            values: [cajas_s, cajas_m, cajas_l, cajas_xl, TotalPrice]
        };
        try {
            const result = await database.query(consultaPedido);
            function devoleverIdPedido(){
                return result.rows[0].id_pedido;
            }
        } catch (err) {
            console.log(err.stack);
        }
        return res.sendStatus(200);
    }
    res.sendStatus(400);
    window.location.href = "fallo_conexion.html";
});
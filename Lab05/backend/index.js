require("dotenv").config();
const express = require("express");
const mongoose = require("mongoose");
const ProductModel = require("./models/ProductModel");

const app = express();

// Middlewares
app.use(express.json());

// CORS
const cors = require("cors");
app.use(cors());

main().catch(err => console.log(err));

async function main() {
    try {
        console.log(`Connecting to DB... ${process.env.MONGODB_URL}`);
        await mongoose.connect(process.env.MONGODB_URL || 'mongodb://127.0.0.1:27017/test');
    } catch (error) {
        console.log("ERROR: Failed connecting to DB!");
        console.log(error);
    } finally {
        await defineRoutes(app);

        let port = process.env.LISTEN_PORT || 8080;
        app.listen(port, () =>
          console.log(`Server up and listening on ${port}...`),
        );
    }
}

async function defineRoutes(app) {
    app.get("/product", (req, res) => {
        res.send({
            success: true,
            products: [
                {
                    name: "Product 1",
                    price: 99.99
                },
                {
                    name: "Product 2",
                    price: 19.99
                }
            ]
        });
    });
}
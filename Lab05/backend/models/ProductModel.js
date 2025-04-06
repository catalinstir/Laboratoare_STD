const mongoose = require("mongoose");

const productSchema = new mongoose.Schema({
    name: {
        type: String,
        required: true,
        min: 3,
        max: 150
    },
    price: {
        type: Number,
        required: true
    }
});
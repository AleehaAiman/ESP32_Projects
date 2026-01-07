const mongoose = require('mongoose');

const recipeSchema = new mongoose.Schema({
    name: String,
    items: Object,
    instructions: [String],
    isFavorite: { type: Boolean, default: false }
});

module.exports = mongoose.model('Recipe', recipeSchema);

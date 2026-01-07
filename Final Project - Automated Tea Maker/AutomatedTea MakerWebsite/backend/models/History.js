const mongoose = require('mongoose');

const historySchema = new mongoose.Schema({
  recipeName: String,
  date: { type: Date, default: Date.now },
  settings: Object,
  duration: Number
});

module.exports = mongoose.model('History', historySchema);

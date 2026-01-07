const mongoose = require('mongoose');

const settingsSchema = new mongoose.Schema({
    userId: { type: String, default: 'default' },
    theme: { type: String, default: 'dark' },
    notifications: { type: Boolean, default: true },
    preferences: { type: Object, default: {} }
});

module.exports = mongoose.model('Settings', settingsSchema);

const express = require('express');
const mongoose = require('mongoose');
const cors = require('cors');
const dotenv = require('dotenv');

// Models
const History = require('./models/History');
const Recipe = require('./models/Recipe');
const Settings = require('./models/Settings');

dotenv.config();

const app = express();
const PORT = process.env.PORT || 5000;

// Middleware
app.use(cors());
app.use(express.json());

// MongoDB Connection
const MONGODB_URI = process.env.MONGODB_URI || 'mongodb://localhost:27017/teamaker';
mongoose.connect(MONGODB_URI)
    .then(() => console.log('Connected to MongoDB'))
    .catch((err) => console.error('MongoDB connection error:', err));

// --- API Routes ---

// 1. Brew History
app.get('/api/history', async (req, res) => {
    try {
        const history = await History.find().sort({ date: -1 });
        res.json(history);
    } catch (err) {
        res.status(500).json({ message: err.message });
    }
});

app.post('/api/history', async (req, res) => {
    const historyItem = new History(req.body);
    try {
        const newHistory = await historyItem.save();
        res.status(201).json(newHistory);
    } catch (err) {
        res.status(400).json({ message: err.message });
    }
});

app.delete('/api/history', async (req, res) => {
    try {
        await History.deleteMany({});
        res.json({ message: 'History cleared' });
    } catch (err) {
        res.status(500).json({ message: err.message });
    }
});

// 2. Recipes
app.get('/api/recipes', async (req, res) => {
    try {
        const recipes = await Recipe.find();
        res.json(recipes);
    } catch (err) {
        res.status(500).json({ message: err.message });
    }
});

app.post('/api/recipes', async (req, res) => {
    const recipe = new Recipe(req.body);
    try {
        const newRecipe = await recipe.save();
        res.status(201).json(newRecipe);
    } catch (err) {
        res.status(400).json({ message: err.message });
    }
});

app.patch('/api/recipes/:id', async (req, res) => {
    try {
        const updatedRecipe = await Recipe.findByIdAndUpdate(req.params.id, req.body, { new: true });
        res.json(updatedRecipe);
    } catch (err) {
        res.status(400).json({ message: err.message });
    }
});

app.delete('/api/recipes/:id', async (req, res) => {
    try {
        await Recipe.findByIdAndDelete(req.params.id);
        res.json({ message: 'Recipe deleted' });
    } catch (err) {
        res.status(500).json({ message: err.message });
    }
});

// 3. Settings
app.get('/api/settings', async (req, res) => {
    try {
        let settings = await Settings.findOne({ userId: 'default' });
        if (!settings) {
            settings = await Settings.create({ userId: 'default' });
        }
        res.json(settings);
    } catch (err) {
        res.status(500).json({ message: err.message });
    }
});

app.put('/api/settings', async (req, res) => {
    try {
        const updatedSettings = await Settings.findOneAndUpdate(
            { userId: 'default' },
            req.body,
            { new: true, upsert: true }
        );
        res.json(updatedSettings);
    } catch (err) {
        res.status(400).json({ message: err.message });
    }
});

app.listen(PORT, () => {
    console.log(`Server is running on port ${PORT}`);
});

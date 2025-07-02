# 🧠 Rustiq AI – Custom C++ LLM Framework

This project is a **from-scratch** implementation of a Large Language Model (LLM) in C++. It includes custom modules for tokenization, training, generation, neural network computation, and attention mechanisms. Designed to be modular, lightweight, and suitable for data analysis and NLP tasks.

---

## 📁 Project Structure

```
ai/
├── include/              # Shared public headers
│   └── rustiq.hpp
│
├── data/                 # Input datasets (e.g. .txt, .csv)
│   └── raw.txt
│
├── models/               # Trained models, weights
│   └── model.bin
│
├── output/               # Inference results, logs
│   └── inference.txt
│
├── src/                  # Core source code
│
│   ├── main.cpp          # Program entry point
│
│   ├── Analyzer/         # Post-analysis (metrics, insights)
│   │   ├── Analyzer.cpp
│   │   └── Analyzer.hpp
│
│   ├── DataFrame/        # Tabular data interface (like Pandas)
│   │   ├── DataFrame.cpp
│   │   └── DataFrame.hpp
│
│   ├── DataLoader/       # Dataset loading & preprocessing
│   │   ├── DataLoader.cpp
│   │   └── DataLoader.hpp
│
│   ├── Insight/          # High-level information extraction
│   │   ├── InsightEngine.cpp
│   │   └── InsightEngine.hpp
│
│   ├── LLM/              # Transformer-based model components
│   │   ├── Transformer.cpp
│   │   ├── Transformer.hpp
│   │   ├── Attention.cpp
│   │   ├── Attention.hpp
│   │   ├── FeedForward.cpp
│   │   ├── FeedForward.hpp
│   │   ├── LayerNorm.cpp
│   │   ├── LayerNorm.hpp
│   │   ├── PositionalEncoding.cpp
│   │   └── PositionalEncoding.hpp
│
│   ├── nn/               # Math engine (tensors, activations, losses)
│   │   ├── Tensor.cpp
│   │   ├── Tensor.hpp
│   │   ├── MatMul.cpp
│   │   ├── MatMul.hpp
│   │   ├── Activation.cpp
│   │   ├── Activation.hpp
│   │   ├── Loss.cpp
│   │   ├── Loss.hpp
│   │   ├── Init.cpp
│   │   └── Init.hpp
│
│   ├── Tokenizer/        # Text encoding (IDs, vocab)
│   │   ├── Tokenizer.cpp
│   │   ├── Tokenizer.hpp
│   │   ├── Vocab.cpp
│   │   └── Vocab.hpp
│
│   ├── TextGen/          # Inference and text generation
│   │   ├── TextGenerator.cpp
│   │   └── TextGenerator.hpp
│
│   ├── Training/         # Training logic (optimizer, scheduler)
│   │   ├── Trainer.cpp
│   │   ├── Trainer.hpp
│   │   ├── Optimizer.cpp
│   │   ├── Optimizer.hpp
│   │   ├── Scheduler.cpp
│   │   └── Scheduler.hpp
│
│   └── Utils/            # Logging, utilities, timing
│       ├── Utils.cpp
│       ├── Utils.hpp
│       ├── Logger.cpp
│       └── Logger.hpp
│
├── tests/                # Unit tests
│   ├── test_tensor.cpp
│   ├── test_tokenizer.cpp
│   └── ...
```

---

## 🧩 Module Responsibilities

| Module         | Description |
|----------------|-------------|
| **LLM/**       | Core transformer model: attention, feed-forward, normalization, etc. |
| **nn/**        | Mathematical backend: tensor operations, matrix multiplication, activations, loss functions |
| **Tokenizer/** | Text tokenization and vocabulary management |
| **Training/**  | Training loop, optimizer (e.g. Adam), learning rate scheduler |
| **TextGen/**   | Generative text output using the trained model |
| **Analyzer/**  | Post-inference analysis and metrics |
| **Insight/**   | Higher-level insight extraction from generated content |
| **DataLoader/**| Loads and formats datasets for training |
| **DataFrame/** | Lightweight data manipulation for tabular formats |
| **Utils/**     | Logging, timers, helpers |
| **tests/**     | Test suite for validating components |

---

## 🚀 Roadmap

- [ ] Implement core `Tensor` class
- [ ] Build basic tokenizer with vocab support
- [ ] Implement Transformer with attention blocks
- [ ] Build training loop and optimizer
- [ ] Test and validate text generation
- [ ] Optional: create CLI or API interface (Go backend, Next.js frontend)

---

## 🛠️ Build Instructions

You can compile the project using CMake:

```bash
mkdir build && cd build
cmake ..
make
./rustiq_ai
```

---

## 📜 License

MIT – Feel free to use, extend, and modify.
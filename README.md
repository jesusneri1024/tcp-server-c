# 🧠 TCP Server in C

This project implements a basic **TCP Echo Server** in C. It listens for a client connection, receives messages, and sends them back exactly as received. It's a solid starting point for learning low-level networking with sockets in C.

---

## 🚀 How to Build

Use CMake to build the project:

```bash
mkdir build
cd build
cmake ..
make
```

This will generate an executable named `servidor`.

---

## ⚙️ How to Use

1. Run the server:

```bash
./servidor
```

2. Connect using `telnet` or `netcat` from another terminal:

```bash
telnet localhost 8080
```

or

```bash
nc localhost 8080
```

Type any message and the server will echo it back.

---

## 📚 Concepts Covered

- TCP socket creation
- Binding to a port
- Listening for connections
- Accepting clients
- Receiving and sending data
- Gracefully closing sockets

---

## 📦 Project Structure

```
tcp-server-c/
├── main.c
├── CMakeLists.txt
├── README.md
└── .gitignore
```

---

## 🛠️ Next Steps

- Handle multiple clients using `select()` or threads
- Convert to a simple HTTP server
- Add logging or command parsing

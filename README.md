# TinyURL 

## Functional Explanation
TinyURL is a URL shortening service that allows users to convert long URLs into shorter, more manageable links. This project provides a simple implementation of such a service using base62 encoding. Users can encode a long URL into a short one and decode it back to the original URL with a guarantee of consistency and correctness.

### Features:
- Encode long URLs into short, unique identifiers.
- Decode short URLs back to the original long URLs.
- Simple in-memory storage for mapping URLs.

---

## Solution Description
This project implements a URL shortening service using the following components:

1. **Base62 Encoding**:
   - Short URLs are generated using base62 encoding (characters `a-z`, `A-Z`, `0-9`).
   - Each URL is assigned a unique index, which is then converted to a base62 string to ensure compactness.

2. **Data Storage**:
   - A simple in-memory array stores mappings between long URLs and their short counterparts.

3. **Key Methods**:
   - `encode`: Converts a long URL to a short URL.
   - `decode`: Retrieves the original URL from a short URL.

### Time and Space Complexity
1. **Encoding**:
   - **Time Complexity**: O(1) - Insertion into the array and generating a short code are constant-time operations.
   - **Space Complexity**: O(N) - Storage requirement grows linearly with the number of URLs.

2. **Decoding**:
   - **Time Complexity**: O(L) - Converting a short code to an index depends on the length of the short code (constant for this implementation).
   - **Space Complexity**: O(1) - No additional space is required for decoding.

### Optimality
The solution is optimal for small-scale usage due to its simplicity and constant-time operations for encoding and decoding. It uses minimal resources and avoids external dependencies, making it ideal for educational purposes or lightweight applications.

---

## Instructions for Cloning and Running

### Prerequisites
- A C compiler (e.g., GCC, Clang).
- Git installed on your machine.

### Steps
1. **Clone the Repository**:
   ```bash
   git clone <repository-url>
   cd <repository-folder>
   ```

2. **Compile the Code**:
   ```bash
   gcc -o tinyurl tinyurl.c
   ```

3. **Run the Program**:
   ```bash
   ./tinyurl
   ```

### Example Usage
Once the program runs, it will:
1. Encode sample URLs provided in the code.
2. Display the shortened URLs.
3. Decode the short URLs back to the original long URLs.

Feel free to modify the `main` function to add more test cases or integrate the solution into a larger system.

---

## Future Improvements
- Add support for persistent storage (e.g., database or file-based storage).
- Implement a web interface for easier interaction.
- Enhance scalability to handle larger datasets and concurrent users.

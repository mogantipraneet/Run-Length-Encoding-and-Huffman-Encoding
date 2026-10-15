# Data Compression using RLE and Huffman Coding

Very simple Computer Networks Lab project in C.

## What it does
- Takes text as input.
- Performs Run Length Encoding (RLE).
- Builds a simple Huffman tree.
- Displays Huffman codes.

## Compile

```bash
gcc compression.c -o compression
```

## Run

Linux:
```bash
./compression
```

Windows:
```bash
compression.exe
```

## Example

Input:
```text
AAAAABB
```

RLE:
```text
5A 2B
```

Huffman:
Characters that appear more frequently receive shorter binary codes.

## Viva explanation

**RLE:** Stores repeated characters as a count and character.

**Huffman:** Counts character frequency, creates a binary tree, and assigns
shorter codes to frequent characters.

Both are lossless compression techniques.

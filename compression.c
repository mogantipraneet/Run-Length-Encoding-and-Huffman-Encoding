/* Data Compression using RLE and Huffman Coding
   Simple Computer Networks Lab Project */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* ---------- RLE ---------- */

void rle(char text[]) {
    int i, count;

    printf("\nRLE Compressed: ");

    for (i = 0; text[i] != '\0'; i++) {
        count = 1;

        while (text[i] == text[i + 1]) {
            count++;
            i++;
        }

        printf("%d%c ", count, text[i]);
    }
}

/* ---------- HUFFMAN ---------- */

struct Node {
    char ch;
    int freq;
    struct Node *left, *right;
};

struct Node* newNode(char ch, int freq) {
    struct Node *node = (struct Node*)malloc(sizeof(struct Node));
    node->ch = ch;
    node->freq = freq;
    node->left = NULL;
    node->right = NULL;
    return node;
}

void printCodes(struct Node *root, int code[], int top) {
    if (root->left) {
        code[top] = 0;
        printCodes(root->left, code, top + 1);
    }

    if (root->right) {
        code[top] = 1;
        printCodes(root->right, code, top + 1);
    }

    if (!root->left && !root->right) {
        printf("'%c' : ", root->ch);

        for (int i = 0; i < top; i++)
            printf("%d", code[i]);

        printf("\n");
    }
}

/* Find the two smallest frequency nodes */
void findTwoSmallest(struct Node *nodes[], int n, int *a, int *b) {
    *a = -1;
    *b = -1;

    for (int i = 0; i < n; i++) {
        if (nodes[i] == NULL)
            continue;

        if (*a == -1 || nodes[i]->freq < nodes[*a]->freq) {
            *b = *a;
            *a = i;
        } else if (*b == -1 || nodes[i]->freq < nodes[*b]->freq) {
            *b = i;
        }
    }
}

void huffman(char text[]) {
    int freq[256] = {0};

    for (int i = 0; text[i] != '\0'; i++)
        freq[(unsigned char)text[i]]++;

    struct Node *nodes[256];
    int n = 0;

    for (int i = 0; i < 256; i++) {
        if (freq[i] > 0)
            nodes[n++] = newNode((char)i, freq[i]);
    }

    if (n == 0)
        return;

    /* Build Huffman tree */
    while (n > 1) {
        int a, b;
        findTwoSmallest(nodes, n, &a, &b);

        struct Node *parent =
            newNode('\0', nodes[a]->freq + nodes[b]->freq);

        parent->left = nodes[a];
        parent->right = nodes[b];

        nodes[a] = parent;
        nodes[b] = nodes[n - 1];
        n--;
    }

    int code[256];

    printf("\nHuffman Codes:\n");
    printCodes(nodes[0], code, 0);
}

/* ---------- MAIN ---------- */

int main() {
    char text[200];

    printf("DATA COMPRESSION USING RLE AND HUFFMAN CODING\n");
    printf("===============================================\n");

    printf("Enter text: ");
    fgets(text, sizeof(text), stdin);

    text[strcspn(text, "\n")] = '\0';

    printf("\nOriginal Text: %s\n", text);

    rle(text);

    huffman(text);

    printf("\n\nRLE replaces repeated characters with count + character.");
    printf("\nHuffman gives shorter binary codes to frequent characters.\n");

    return 0;
}

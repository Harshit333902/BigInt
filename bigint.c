#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

struct BigInt {
    int digit;
    struct BigInt *next;
    int length;
};

typedef struct BigInt BigInt;

// Function to reverse the linked list
void reverse(BigInt **p) {
    BigInt *current = *p;
    BigInt *prev = NULL;
    BigInt *next;

    while (current != NULL) {
        next = current->next;
        current->next = prev;
        prev = current;
        current = next;
        (*p)->length++;
    }

    *p = prev;
}

// Function to subtract two polynomials
BigInt *polySub(BigInt *poly1, BigInt *poly2) {
    int borrow = 0;
    reverse(&poly1);
    reverse(&poly2);
    BigInt *result = NULL;

    // Ensure both polynomials have the same length
    while (poly1->length < poly2->length) {
        BigInt *temp = (BigInt *)malloc(sizeof(BigInt));
        temp->digit = 0;
        temp->next = poly1;
        poly1 = temp;
        poly1->length++;
    }

    while (poly1 != NULL || poly2 != NULL || borrow) {
        int x = borrow;
        BigInt *temp = (BigInt *)malloc(sizeof(BigInt));

        if (poly1) {
            x += poly1->digit;
            poly1 = poly1->next;
        }

        if (poly2) {
            x -= poly2->digit;
            poly2 = poly2->next;
        }

        if (x < 0) {
            x += 10;
            borrow = -1;
        } else {
            borrow = 0;
        }

        temp->digit = x;
        temp->next = result;
        result = temp;
    }

    reverse(&result);

    return result;
}

// Function to multiply two polynomials
BigInt *polyMulti(BigInt *poly1, BigInt *poly2) {
    BigInt *result = NULL;
    long long N = 1000000007;
    long long num1 = 0;
    long long num2 = 0;

    while (poly1 || poly2) {
        if (poly1) {
            num1 = ((num1) * 10) % N + poly1->digit;
            poly1 = poly1->next;
        }

        if (poly2) {
            num2 = ((num2) * 10) % N + poly2->digit;
            poly2 = poly2->next;
        }
    }

    long long product = num1 * num2;
    // Implement the logic to create the result polynomial from the product
    // ...

    return result;
}

// Function to add two polynomials
BigInt *polyAdd(BigInt *poly1, BigInt *poly2) {
    int x, carry = 0;
    BigInt *result = NULL;
    BigInt *temp;
    reverse(&poly1);
    reverse(&poly2);

    while (poly1 != NULL || poly2 != NULL || carry) {
        temp = (BigInt *)malloc(sizeof(BigInt));
        x = carry;

        if (poly1) {
            x += poly1->digit;
            poly1 = poly1->next;
        }

        if (poly2) {
            x += poly2->digit;
            poly2 = poly2->next;
        }

        carry = x / 10;
        x %= 10;
        temp->digit = x;
        temp->next = result;
        result = temp;
    }

    return result;
}

// Function to print a polynomial
void print(BigInt *poly) {
    BigInt *current = poly;

    while (current != NULL) {
        printf("%d", current->digit);
        current = current->next;
    }
}

// Function to create a new node for a polynomial
BigInt *createNode(int digit) {
    BigInt *newNode = (BigInt *)malloc(sizeof(BigInt));
    newNode->digit = digit;
    newNode->next = NULL;
    return newNode;
}

// Function to input a polynomial from the user
BigInt *input() {
    BigInt *temp = NULL;
    char ch;

    printf("Enter big integer:\n");

    while (1) {
        ch = getchar();
        if (ch == '\n' || !isdigit(ch)) {
            break;
        }

        int digit = ch - '0';
        BigInt *newNode = createNode(digit);

        if (temp == NULL) {
            temp = newNode;
        } else {
            newNode->next = temp;
            temp = newNode;
        }
    }

    return temp;
}

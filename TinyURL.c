#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_URLS 1000          // Maximum number of URLs
#define SHORT_CODE_LENGTH 6    // Length of the short code
#define BASE_URL "http://tinyurl.com/"

// Characters for base62 encoding
const char base62[] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";

// Solution class-like structure
typedef struct {
    char* database[MAX_URLS];  // Stores the original URLs
    int urlCount;              // Counter for URLs
} Solution;

// Helper function: Convert a number to a base62 string
void toBase62(int num, char* shortCode) {
    for (int i = SHORT_CODE_LENGTH - 1; i >= 0; i--) {
        shortCode[i] = base62[num % 62];
        num /= 62;
    }
    shortCode[SHORT_CODE_LENGTH] = '\0';
}

// Initializes the Solution object
Solution* solutionCreate() {
    Solution* obj = (Solution*)malloc(sizeof(Solution));
    obj->urlCount = 0;
    memset(obj->database, 0, sizeof(obj->database));
    return obj;
}

// Encodes a long URL to a tiny URL
char* encode(Solution* obj, char* longUrl) {
    if (obj->urlCount >= MAX_URLS) {
        printf("Database full. Cannot encode more URLs.\n");
        return NULL;
    }

    // Store the URL in the database
    obj->database[obj->urlCount] = strdup(longUrl);

    // Generate the short code
    char shortCode[SHORT_CODE_LENGTH + 1];
    toBase62(obj->urlCount, shortCode);

    // Create the full tiny URL
    char* tinyUrl = (char*)malloc(strlen(BASE_URL) + SHORT_CODE_LENGTH + 1);
    sprintf(tinyUrl, "%s%s", BASE_URL, shortCode);

    // Increment the counter
    obj->urlCount++;

    return tinyUrl;
}

// Decodes a tiny URL to the original URL
char* decode(Solution* obj, char* shortUrl) {
    // Extract the short code from the tiny URL
    char* shortCode = shortUrl + strlen(BASE_URL);

    // Convert the short code back to an index
    int index = 0;
    for (int i = 0; i < SHORT_CODE_LENGTH; i++) {
        if (shortCode[i] >= 'a' && shortCode[i] <= 'z')
            index = index * 62 + (shortCode[i] - 'a');
        else if (shortCode[i] >= 'A' && shortCode[i] <= 'Z')
            index = index * 62 + (shortCode[i] - 'A' + 26);
        else if (shortCode[i] >= '0' && shortCode[i] <= '9')
            index = index * 62 + (shortCode[i] - '0' + 52);
    }

    // Retrieve the original URL from the database
    if (index < 0 || index >= obj->urlCount) {
        printf("Invalid short code.\n");
        return NULL;
    }

    return obj->database[index];
}

// Frees the Solution object
void solutionFree(Solution* obj) {
    for (int i = 0; i < obj->urlCount; i++) {
        free(obj->database[i]);
    }
    free(obj);
}

// Test the Solution class
int main() {
    Solution* obj = solutionCreate();

    // Test URLs
    char* url1 = "https://www.example.com";
    char* url2 = "https://www.another-example.com";
    char* url3 = "https://www.yetanotherexample.com";

    // Encode URLs
    char* shortUrl1 = encode(obj, url1);
    char* shortUrl2 = encode(obj, url2);
    char* shortUrl3 = encode(obj, url3);

    printf("Encoded URLs:\n");
    printf("%s -> %s\n", url1, shortUrl1);
    printf("%s -> %s\n", url2, shortUrl2);
    printf("%s -> %s\n", url3, shortUrl3);

    // Decode URLs
    printf("\nDecoded URLs:\n");
    printf("%s -> %s\n", shortUrl1, decode(obj, shortUrl1));
    printf("%s -> %s\n", shortUrl2, decode(obj, shortUrl2));
    printf("%s -> %s\n", shortUrl3, decode(obj, shortUrl3));

    // Free allocated memory
    free(shortUrl1);
    free(shortUrl2);
    free(shortUrl3);
    solutionFree(obj);

    return 0;
}

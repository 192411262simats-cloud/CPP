// INTENTIONALLY UNSAFE EXAMPLE FOR COMPILER-WARNING EVIDENCE ONLY.
// Do not call invalidReference() or use the returned reference.

int& invalidReference() {
    int localValue = 50;
    return localValue; // Warning: reference to local variable is returned.
}

int main() {
    // The unsafe function is deliberately not called.
    return 0;
}

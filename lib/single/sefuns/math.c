float diminishing_returns(mixed val, mixed scale) {
    float mult, trinum;
    if(val < 0)
        return -diminishing_returns(-val, scale);
    mult = val / to_float(scale);
    trinum = (sqrt(8.0 * mult + 1.0) - 1.0) / 2.0;
    return trinum * scale;
}

int minimum(int num1, int num2) {
    return (num1 < num2)? num1 : num2;
}

int maximum(int num1, int num2) {
    return (num1 > num2)? num1 : num2;
}
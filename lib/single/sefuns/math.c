float diminishing_returns(mixed val, mixed scale) {
    float mult, trinum;
    if(val < 0)
        return -diminishing_returns(-val, scale);
    mult = val / to_float(scale);
    trinum = (sqrt(8.0 * mult + 1.0) - 1.0) / 2.0;
    return trinum * scale;
}
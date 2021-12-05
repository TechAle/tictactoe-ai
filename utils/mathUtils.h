/*
 * @Author: TechAle
 * @Since: 05/11/21
 */


// Modified version of https://stackoverflow.com/questions/16826422/c-most-efficient-way-to-convert-string-to-int-faster-than-atoi/16826908
static int fast_atoi( const string& str, int len )
{
    // Start from 0
    int val = 0;
    for(int i = 0; i < len - 1; i++) {
        // Get the value
        char value = str[i];
        // Add the current value to the old one * 10
        val = val*10 + (value - '0');
    }
    // Return
    return val;
}
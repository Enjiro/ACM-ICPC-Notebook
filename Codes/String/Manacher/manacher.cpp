char s[200000];
int n;
// Encontrar palindromos - inicializa d1 e d2 com zeros, e eles guadram 
// o numero de palindromos centrados na posicao i (d1[i] e d2[i])
// impar 
int d1[200000], d2[200000];
void imp(){
   int l=0, r=-1;
   for (int i=0; i<n; ++i) {
       int k = (i>r ? 0 : min (d1[l+r-i], r-i)) + 1;
       while (i+k < n && i-k >= 0 && s[i+k] == s[i-k])  ++k;
       d1[i] = --k;
       if (i+k > r)
           l = i-k,  r = i+k;
   }
}
// par 
void par(){
   int l=0, r=-1;
   for (int i=0; i<n; ++i) {
       int k = (i>r ? 0 : min (d2[l+r-i+1], r-i+1)) + 1;
       while (i+k-1 < n && i-k >= 0 && s[i+k-1] == s[i-k])  ++k;
       d2[i] = --k;
       if (i+k-1 > r)
           l = i-k,  r = i+k-1;
   }
}

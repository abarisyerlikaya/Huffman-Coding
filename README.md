# Huffman Coding
  A program which compresses given string by Huffman Coding and generates it's Huffman Tree.

### What is Huffman Coding?
  In computer science and information theory, a Huffman code is a particular type of optimal prefix code that is commonly used for lossless data compression.

![](https://upload.wikimedia.org/wikipedia/commons/thumb/8/82/Huffman_tree_2.svg/625px-Huffman_tree_2.svg.png)

  Huffman tree generated from the exact frequencies of the text "this is an example of a huffman tree". The frequencies and codes of each character are below. Encoding the sentence with this code requires 135 (or 147) bits, as opposed to 288 (or 180) bits if 36 characters of 8 (or 5) bits were used. (This assumes that the code tree structure is known to the decoder and thus does not need to be counted as part of the transmitted information.)

Char | Freq |	Code
-----|------|-----
space |	7	| 111
a	| 4	| 010
e	| 4	| 000
f	| 3	| 1101
h	| 2	| 1010
i	| 2	| 1000
m	| 2	| 0111
n	| 2	| 0010
s	| 2	| 1011
t	| 2	| 0110
l	| 1	| 11001
o	| 1	| 00110
p	| 1	| 10011
r	| 1	| 11000
u	| 1	| 00111
x	| 1	| 10010

(Image, table and information from Wikipedia)

### Screenshots
![](https://i.imgur.com/QPOuGkM.png)

![](https://i.imgur.com/6tOfWke.png)

![](https://i.imgur.com/ariSOeV.png)

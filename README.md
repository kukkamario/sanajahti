Simple resolver with UI for Sanajahti

Finds all words within 4x4 grid
Is stupid with handling non-ascii characters because I wanted to implement the core algorithm
without libraries and standard C++ encoding functionality is painful, or was much more painful
when this was originally written years ago. So I just replaced Ä with 1 and Ö with 2 in sanat.txt.
Bit of a hack but works well enough.

Usage:
Program expects "sanat.txt" to be in working directory and each line to contain one word.

Input 4x4 grid of words left to right, up-to-down order to the left side text box and press "Resolve".
Found words are listed in the list under the button. Pressing any of the found words will display swipe
order of the letters in the top right grid.

Included sanat.txt is generated from Kotus Nykysuomen sanalista
https://kotus.fi/sanakirjat/kielitoimiston-sanakirja/nykysuomen-sana-aineistot/nykysuomen-sanalista/
  
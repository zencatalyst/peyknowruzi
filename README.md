<h1 align="center">Welcome to the README of PeykNowruzi 👋</h1>

> PeykNowruzi is a basic ASCII art generator that can draw any desired shape using only four characters ('/', '\\', '|', '-') on the console/cmd/terminal screen given that you've provided the corect coordinates of each character.<br />


## 🚀 How to use the program:
Below you can see the instructions on how to interact with the program PeykNowruzi.

- Run the `runPeykNowruzi_Windows.exe` or `runPeykNowruzi_Linux` file. Below is an example:

```sh
C:\Users\joel\Desktop>runPeykNowruzi_Windows.exe
```

- On the first line enter half of the number n of characters you want to be printed (that is to say e.g. if you want to draw n=12 characters then you have to enter 12/2=**6**).

```sh
6
```

- Now you will need to give n/2 lines of input to the program each one containing the coords (x1, y1) of the first character
and the coords (x2, y2) of the second character. In the following example, 6 lines are passed to the program as input containing the coords for 12 characters.

```sh
0 1 1 0
2 0 3 1
1 1 2 1
1 2 2 2
0 2 1 3
2 3 3 2
```

**Additional guidance related to the previous step**

- Enter 4 numbers at each line using this format: `x1 y1 x2 y2`

- Similar formats can be used like for example: `x1    y1 x2           y2`. [Notice that entering multiple spaces or tabs won't cause any problems as long as all of the four numbers are at the same line.]

```sh
0     2 1                 3
       2    3           3  2
```

- `x1` (is the x of the first character) , `x2` (is the x of the second character) etc.

- Note that at least one **_space_** or **_tab_** character should be inserted between each number in order for the program to work as expected so e.g. the following formats are invalid: `x1y1x2y2` , `x1 y1x2 y2` , etc.

```sh
0213
2 33 2
```

- Press <kbd>enter</kbd> after you've typed the four numbers of each line to go to the next line.

- Once you have typed the last (n/2 th) line of coords, press <kbd>enter</kbd> to see the result (a figure drawn on the screen).

```sh
 /\
/--\
\--/
 \/
```

- **This is how it will look like as a whole:**

```sh
C:\Users\joel\Desktop>runPeykNowruzi_Windows.exe
6
0 1 1 0
2 0 3 1
1 1 2 1
1 2 2 2
0 2 1 3
2 3 3 2
 /\
/--\
\--/
 \/
```

## ✨ How to pass an input file to the program:

An alternative and easier way to provide input data to the program is to pass an input text file containing all the required data in order to execute the program.
So there is no need to type all of the numbers (coordinates) using the keyboard.

A sample input file called `PeykNowruzi_sample-input.txt` can be found inside '_Sample Inputs_' directory.

Below is an example of how you can achieve this using **<** operator:

```sh
C:\Users\joel\Desktop\peyknowruzi\Executables>runPeykNowruzi_Windows.exe < "C:\Users\joel\Desktop\peyknowruzi\Sample Inputs\PeykNowruzi_sample-input.txt"
```

**Here is a demo:**

<p align="center">
  <img width="900" align="center" src="https://user-images.githubusercontent.com/73937934/139603583-cfa63844-4bca-4675-8188-54916907886a.gif" alt="Demo of passing input file"/>
</p>

## 🤝 Contributing

Contributions, issues and feature requests are welcome.<br />
Thanks a ton for your cooperation!

## Author

👤 **Kasra Hashemi**

- Github: [@zencatalyst](https://github.com/zencatalyst)

## Show your support

Please ⭐️ this repository if this small project helped you!

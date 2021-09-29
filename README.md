# NPRG041 2021/22 C++ labs

*Disclaimer and credits:* This page was put together using other teachers web pages:
* <https://e-x-a.org/mff/cpp20/>
* <https://www.ksi.mff.cuni.cz/teaching/nprg041-zavoral-web/cviceni.html>


## Important info

* every Friday at 10:40 at SU2

* lecture web at <https://www.ksi.mff.cuni.cz/teaching/nprg041-web/>

* taught by Tomas Drozdik (<drozdik.tomas@gmail.com>)

* Mattermost group only channel - <https://ulita.ms.mff.cuni.cz/mattermost/ar2122zs/channels/nprg041-cpp-drozdik> <- *primary method of communication*

* information about what was/is/will be happening in labs will be present in this repo

* every student has his/her own repository under this [GitLab group](https://gitlab.mff.cuni.cz/teaching/nprg041/2021-22/drozdik) where he/she should submit:
    * lab work
    * individual project

* facing any issue contact me via email or Mattermost *in advance*


## C++ resources

* Any good book about C++ will do..
    * Some are recommended in the lecture.
    * Personally I've read [C++ Primer by Lippman,StanleyB.](amazon.com/Primer-5th-Stanley-B-Lippman/dp/0321714113) because it seemed more accessible than [The C++ Programming Language](https://www.amazon.com/C-Programming-Language-4th/dp/0321563840), by the father of the C++ Bjarne Stroustrup himself, but I did not really read that one so I may be wrong.
    * Beware that C++ is evolving language (current version is C++20) while the C++ Primer covers only up to version C++14 I think. General rule of thumb is that newer is better and more accessible. Anyway always try to search for the latest edition, but don't attempt to look for a book covering *the newest C++* stuff.
    * Some of the books are available in the MFF library, otherwise you might try [NTK](https://www.techlib.cz/cs/).

* If you are brave you can try to read the [C++ standard itself](http://www.open-std.org/jtc1/sc22/wg21/).

* If standard is not your thing try one of these:
    * [cppreference.com](https://en.cppreference.com/w/)
    * [cplusplus.com](https://www.cplusplus.com/)

* I can also recommend some YouTube channels:
    * [CppCon](https://www.youtube.com/user/CppCon) - The C++ Conference
        - for basics and fundamentals try their [Back to Basics track](https://www.youtube.com/user/CppCon/search?query=back%20to%20basics)
    * [C++ Weekly with Jason Turner](https://www.youtube.com/user/lefticus1) - channel with lots of videos covering many C++ concepts and caveats, if you struggle with particullar one these might come in handy.


## Lab credit requirements

### 1. Lab activity
To get the credit, you have to attend the course reasonably (at least accordingly to your knowledge of the topic).
Attendance will be tracked by contributions to your Gitlab repository dedicated for this lab.
Ideally create a separate folder for each lab with all your work per that lab.

Under normal circumstaces you are allowed to have 3 absences (otherwise refer to the last point in the first section).

### 2. Homeworks
There will be 2 assignments in ReCodex.
Make sure you are registered to the correct student group, use the [SIS Integration module](https://recodex.mff.cuni.cz/app/sis-integration) then you should be able to see the course in the dashboard.

Deadlines will be announced as the assignements will be available.

For more information about points and grading refer to lecture web.

### 3. Individual project
Each student has to create an individual project and submit it to get the credit. Topics of the projects may vary wildly, but you should discuss your topic before the end of November so that it is agreed upon. Size of the project is not an issue and largely depends on the topic, around 500 lines of (neat) C++ code is a good guideline (on the other hand, packing the same functionality into a smaller program using e.g. advanced language features is even better).

**Deadlines:**

| Date                 | Required action |
|----------------------|-----------------|
|*November 20th, 2021* | Topic agreed upon, written down in SIS. Send me an e-mail to make sure the topic is confirmed and added to SIS.
|*March 2022*          | Recommended time of submission.
|*April 30th 2022*     | Deadline for the first submission attempt. Project should be in the Gitlab with its whole development history (not a few mega-commits), documentation, installation instructions and demo instructions!
|*May 28th 2022*       | Deadline for the last submission attempt includinng all fixes.

**Submission guidelines:**

* Code history should be well documented in the Gitlab. Try to be a good developer:
    * Split the code contributions to reasonable size commits and strictly avoid one mega commit.

    * Write good commit messages:
        - Good rule: "If applied, this commit will \<your commit message\>".
        - When in doubt search for "How to write good commit messages".

    * Keep your repo clean:
        - Split it to folders, since you need to have both lab activity and this project in there.
        - Don't add generated or temporary files.
        - Pick your workflow and stick to it.
        - Keep in mind that the repo is public - make yourself proud! :)

* Make the code portable — it should not depend on the platform unless it is, by design, tied to that platform. UNIX projects should work on Linuxes in the computer lab. Please void Windows-specific projects.

* Avoid code bloat, library bundling and excessive media. Maximum size of your final program is limited to 1MB.

* Pick your prefered code style and stick to it!

* Do not over-engineer, avoid feature creep. The simplest project that satisfies the following conditions will do:
    * There’s a reasonable amount of C++ that shows you know what you’re doing.

    * It does not crash, in particular it does not dereference invalid pointers, cause leaks, or torture the memory in any other way.

    * It does not contain any inefficiencies that could be fixed by better C++.

    * It provably does what the topic says, and it can be demonstrated on an example use-case of reasonable complexity.

    * The code has sufficient comments. If you are unsure if you should add comment somewhere, try to tear the surrounding program block or function out of context, and ask yourself if anyone can still fully understand what it does (and why). If not, it needs comments. Note that comments should not rephrase what the code does e.g.
    ``` c++
    int getVal() {return value;} //returns the value
    ```

    * Note that primitive accessor functions that give access to unnecessarily-private member variables, such as the one shown above, are artifacts of misinterpretation of OOP principles that vastly reduce the extensibility of the code (although common even in advanced Java and C# courses!) and should be avoided! In C++, avoid all such waste code that does nothing.

    * If the topic is a data structure, include a comparison with a naive approach or some C++ counterpart (std::chrono provides timers). Note that your data structure does not need to “win” the comparison (that’s the topic of the HPC course). You should only provide a reasonable testing framework to assess the performance.

* Having received your program, I should be able to convince myself that it works in less than around 15 minutes. You can help it a lot:
    * Include a file INSTALL (.md) that describes how to make it work on a fitting computer configuration.
        - *Better:* How to make it work on computers in MFF’s computer lab.
        - *Best:* Add a Makefile/CMake/Dockerfile/script that works in the lab.)

    * Include a file DEMO or TUTORIAL that describes what should I do with the compiled program to see all the important functionality as quickly as possible.
        - *Better:* add a script that does it.

    * If the DEMO requires some data for the demonstration, include it!
        - *Advice:* If I’m forced to create testing data by hand, it will take more than 15 minutes. Also, result will contain lots of hideous corner cases.

    * If the source code is big, include INTERNALS file that describes which parts of the functionality can be found in which part/file of the code. This is sometimes also called “programmer documentation” or “hacking guide”. Imagine it as a signpost, compare with artist’s impression thereof.

    * If all documentation parts are favorably small, pack them together into one README.

**Useful libraries for the projects:**

* For games and simulations with graphics, try OpenGL. There are lots of ways to get an OpenGL viewport for your program, the easiest of them is probably the [GLUT](https://www.opengl.org/resources/libraries/glut/) library. You might also want to see [SDL](http://wiki.libsdl.org/FrontPage) that is commonly used for portable games, or the newer alternative [SFML](https://www.sfml-dev.org/). The following sites provide a good introduction to modern OpenGL: <open.gl> and <learnopengl.com>.

* For a GUI in games, use [ImGUI](https://github.com/ocornut/imgui)

* For user interaction in console, use [readline](https://en.wikipedia.org/wiki/GNU_Readline) and possibly [ncurses](https://en.wikipedia.org/wiki/Ncurses) (tutorial [here](https://www.viget.com/articles/game-programming-in-c-with-the-ncurses-library/))

* For parsing commandline arguments, use [getopt](https://linux.die.net/man/3/getopt)

* Using the standard Berkeley sockets for network communication is certainly adventurous (if writing a server application, remember to [poll correctly](http://software.schmorp.de/pkg/libev.html)). Alternatively, use some reasonable wrapper for basic communication, like [0MQ](https://zeromq.org/).

* If you need to parse/produce JSON and serialize any data, use [nlohmann’s json](https://github.com/nlohmann/json)

* If you need to save data reliably to some kind of a database, use [sqlite3](https://sqlite.org/index.html)

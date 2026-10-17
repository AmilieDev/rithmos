# Standards of Code for this project.
This file contains standards of code for this project, and it is requested that you review it BEFORE you code. Not after. I want to maintain a consistently readable code style that anyone can understand in a clean way.

I don't expect it to be perfect, because I won't be perfect either and I understand sometimes you'll accidentally violate these standards - just be respectful about it, and I'll be respectful to you and these will help make contributing again in the future ten times easier than having to deal with nightmare spaghetti code.

## 1; File Headers and Licensing
All source files, even headers, should have a short header containing the projects license, the author of the file; the first created date and a brief explaination of what the file does.

You should use the following template:

```
// GPL-V2.0
// [Author]; [Date]
// [Short explaination of the file here]
```

If you are making a significant change to a file; instead of replacing the existing author, add yourself on BENEATH them. For example:

```
// GPL-V2.0
// AmilieDev; 16/10/2026
// Contributor1; 20/12/2026
// Wow. This is a short explaination.
```

If you forget a header, don't worry - a reviewer will add one for you. Or, if there's a lot of files, will send you away to add them yourself with a direct link to this guide.

Keep the following in mind though;

- Don't remove any existing copyright or attribution notices.
- Don't write a full essay to explain a file unless its GENUINELY complex. Keep it simple.
- Use appropriate comment syntax for the files language - it may not be C. Adapt it.

## 2; Code Naming Conventions
When writing code for the project you should use **snake_case**. This applies to literally everything. For example:

```c
int current_track = 0;
int total_tracks = 15;

void load_audio_file(void);
void stop_audio_playback(void);
```

Please avoid using camelCase, or PascalCase for variables and functions. You also **SHOULDN'T** be adding leading or trailing underscores. There **are** exceptions to this though. When using an external library, or engaging with system calls and APIs you may need to use PascalCase or camelCase, in that case - exceptions can be made.

Please **do not** rename third party identifiers just to make them align with this standard. This is an INTERNAL PROJECT STANDARD and does NOT apply outside of the project.

### 2.1; Constants and Macros
Please use constants and macros in **UPPER_SNAKE_CASE**. This let's them be distinguised from ordinary variables.

```c
#define MAX_AUDIO_CHANNELS 8
```

## 3; Indentation and Formatting
This standard, is the standard that pisses me off the most and so I will be the most harsh about. You **MUST NOT** use spaces as indentation at ALL. You may only use **TAB**. I understand some people rather use space, but for this project and for my own sanity - TAB BASED INDENTATION ONLY PLEASE.

Do NOT submit code with spaces, any number, being used for indentation. IT WILL BE REJECTED. I don't care how braces are positioned though, just be consistent with it.

Some extra rules.
- Avoid any trailing whitespaces.
- End all files with a new line (just use Return on your keyboard).
- Don't put unrelated statements on one line.
- Avoid long lines where possible.
- Use blank lines to seperate different logical sections of code.
- Don't reformat entire files for small changes; I don't want to read 500 lines of reformatting for 2 lines of meaningful change

## 4; Making PRs
When making a PR, please follow this specific standard:

```
Fix: Updated [blah blah blah]
```

It must follow this standard. Do not make bullshit PR messages such as

```
dsaiudashijdahjk
Updated file
Changed readme.md
```

Actually describe what you've done.

# Exercise Sheet 8 — Outlook

*due on 14 January 2020*

## Task 1 (2 Points)

Revisit the *Advanced Template* slides.

Prepare the `has_print_to` example of slide 18 for presentation.
You'll have to explain all parts step by step like in the lecture.

## Task 2 (2 Points)

In case you are doing networking in C++, consider [Boost Asio](https://www.boost.org/doc/libs/1_72_0/doc/html/boost_asio.html).
For this task, investigate the [chat server example](https://www.boost.org/doc/libs/1_72_0/doc/html/boost_asio/example/cpp11/chat).

Your presentation should explain the overall architecture and focus on the session management mechanism.
Especially the use of `std::enable_shared_from_this`.

## Task 3 (4 Points)

Use [Boost Spirit](https://www.boost.org/doc/libs/1_72_0/libs/spirit/doc/html/index.html) to create a parser for the [Netpbm Image Format](https://en.wikipedia.org/wiki/Netpbm_format). It should support portable pixmap images in ASCII and binary (magic numbers: `P3` and `P6`).

Test your implementation by loading a test image and applying some image transformation.
Save the transformation result as portable pixmap image, so it can be viewed.

*Note 1:* You may ignore the 16-bit extension.

*Note 2:* [ImageMagick](https://imagemagick.org/) supports Netpbm.
Use `-depth 8` to force 8-bit colour channels and `-compress none` to force ASCII output.

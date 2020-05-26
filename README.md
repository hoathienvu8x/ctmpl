======
C++ Template Engine for HTML/CSS/JavaScript
======

> This project clone from [melpon/ginger](https://github.com/melpon/ginger) and modified, i'll develop on base source.

Template is here

.. sourcecode:: html

  <html>
    <head>
      <title>${title}</title>
    </head>
    <body>
      <p>List of values:</p>
      <ul>
        $for x in xs {{
          $if x.enable {{
            <li><a href="${x.url}">${x.value}</a></li>
          }}
        }}
      </ul>
    </body>
  </html>

Source code is here

.. sourcecode:: cpp

  #include <iostream>
  #include <vector>
  #include <map>
  #include <fstream>
  #include <string>
  #include "chtml.h"

  int main() {
      std::vector<std::map<std::string, ginger::object>> xs;
      xs.push_back({
          { "enable", true },
          { "url", "http://example.com" },
          { "value", "Example" },
      });
      xs.push_back({
          { "enable", false },
          { "url", "undefined" },
          { "value", "Test" },
      });
      xs.push_back({
          { "enable", true },
          { "url", "http://google.com" },
          { "value", "Google" },
      });

      std::map<std::string, ginger::object> t;
      t["title"] = "Sample Site";
      t["xs"] = xs;

      std::stringstream ss;
      ss << std::cin.rdbuf();
      try {
          std::string html = "";
          std::ifstream is ("sample.html", std::ifstream::binary);
          if (is) {
              is.seekg (0, is.end);
              int length = is.tellg();
              is.seekg (0, is.beg);
              char * buffer = new char [length];
              is.read (buffer,length);
              if (is) {
                  html = std::string(buffer, length);
              }
              is.close();
              delete[] buffer;
              ctmpl::parse(html, t);
          }
      } catch (ctmpl::parse_error& error) {
          std::cerr << error.long_error() << std::endl;
      }
  }

Result

.. sourcecode:: html

  <html>
    <head>
      <title>Sample Site</title>
    </head>
    <body>
      <p>List of values:</p>
      <ul>
        
          
            <li><a href="http://example.com">Example</a></li>
          
        
          
        
          
            <li><a href="http://google.com">Google</a></li>
          
        
      </ul>
    </body>
  </html>

Requirements
============

Input
-----

- below expression should be valid

  .. sourcecode:: cpp

    auto first = std::begin(input);
    auto last = std::end(input);

- first, last should be ForwardIterator.


Dictionary
----------

- Below expressions should be valid

  .. sourcecode:: cpp

    std::string var;
    auto it = dic.find(var);
    it != dic.end();

- Type of it->second should be object.

Output
------

- Below expression should be valid

  .. sourcecode:: cpp

    // Output output; // default constructible is not required.
    // For any ForwardIterator first, last
    output.put(first, last);
    output.flush();

Reference
=========

object
------

Class ``object`` can construct from any value.

.. sourcecode:: cpp

  class object {
  public:
      object() = default;
      object(const object&) = default;
      object(object&&) = default;
      object& operator=(const object&) = default;
      object& operator=(object&&) = default;

      template<class T> object(T v);
      template<class T> void operator=(T v);
  };

parse
-----

.. sourcecode:: cpp

  template<class Input, class Dictionary>
  void parse(Input&& input, Dictionary&& t);
  template<class Input, class Dictionary, class Output>
  void parse(Input&& input, Dictionary&& t, Output&& out);

  template<class Dictionary>
  void parse(const char* input, Dictionary&& t);
  template<class Dictionary, class Output>
  void parse(const char* input, Dictionary&& t, Output&& out);

Template Syntax Specification
=============================

::

  <root> = <block>
  <block> = (<char> | <$comment> | <$for> | <$if> | <$variable> | $$ | ${{ | $}}) <block> | <eof>
  <char> = any character without '$'
  <$comment> = $#<comment-char>*
  <comment-char> = any character without '\n' and <eof>
  <$for> = $for <var-name> in <var> {{ <block> }}
  <$if> = $if <var> {{ <block> }} ($elseif <var> {{ <block> }})? ($else {{ <block> }})?
  <$variable> = ${<var>}
  <var> = <var-name>(.<var-name>)*
  <var-name> = <var-char>+
  <var-char> = any character without <whitespace>, '.', '{' or '}'
  <whitespace> = c <= 32 where c is character

MIT License

Copyright (c) 2017 melpon

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
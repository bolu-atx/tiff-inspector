#include <iostream>

#include "ftxui/dom/elements.hpp"
#include "ftxui/screen/screen.hpp"
#include "ftxui/screen/string.hpp"

int main(void) {
  using namespace ftxui;

  auto summary = [&] {
    auto content = vbox({
        hbox({text(L"- done: "), text(L"3") | bold}) | color(Color::Purple),
        hbox({text(L"- active: "), text(L"2") | bold}) | color(Color::RedLight),
        hbox({text(L"- queue:  "), text(L"9") | bold}) | color(Color::Red),
    });

    return window(text(L" Summary "), content);
  };

  auto filename = [&] {
    const auto content = vbox({
      hbox({
           text(L"/home/blu/example.txt") | color(Color::Red),
           text(L"   ") | flex_grow,
           text(L"size: 10Mb  ") | color(Color::Green),
           text(L"Bit-depth: 10Mb  ") | color(Color::Green),
           text(L"Compresion: 10Mb  ") | color(Color::Green),
           }),
    });
    return window(text(L"Filename"), content);
  };

  auto document =  //
      vbox({
          filename(),
          hbox({
              summary() | flex_grow,
              summary() | flex,
              summary() | flex,
          }),
          summary(),
          summary(),
      });

  // Limit the size of the document to 80 char.
  document = document | size(WIDTH, LESS_THAN, 150) | size(HEIGHT, GREATER_THAN, 20);

  auto screen = Screen::Create(Dimension::Full(), Dimension::Fit(document));
  Render(screen, document);
  std::cout << screen.ToString() << std::endl;
  return EXIT_SUCCESS;
}

#include "graph.hpp"

#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>

using Simulation = std::vector<epidemy::Model>;

void display(Simulation const& simulation) {
  sf::RenderWindow m_window(sf::VideoMode(800, 600), "SIR model");

  while (m_window.isOpen()) {
    sf::Event event;
    while (m_window.pollEvent(event)) {
      if (event.type == sf::Event::Closed) {
        m_window.close();
      }
    }

    m_window.clear(sf::Color::White);

    {  // Axes, grid
      sf::RectangleShape line_v(sf::Vector2f(5.f, 530.f));
      line_v.setFillColor(sf::Color::Black);
      line_v.setPosition(50.f, 50.f);
      sf::RectangleShape line_o(sf::Vector2f(725.f, 5.f));
      line_o.setFillColor(sf::Color::Black);
      line_o.setPosition(50.f, 580.f);
      m_window.draw(line_o);
      m_window.draw(line_v);

      for (int d = 0; d < 20; ++d) {
        sf::RectangleShape grid_line_o(sf::Vector2f(725.f, 1.f));
    
        grid_line_o.setPosition(50.f, 50+d*26.25);
        grid_line_o.setFillColor(sf::Color(150, 150, 150));
        m_window.draw(grid_line_o);
      }
    }

    {  // Points
      int i = 0;
      for (auto& c : simulation) {
        float n = 55 + i * 8;

        sf::CircleShape S_circle(2.5f);
        S_circle.setFillColor(sf::Color::Green);
        float y_s = 575 - (c.S * 0.0026);
        S_circle.setPosition(n, y_s);
        m_window.draw(S_circle);

        sf::CircleShape I_circle(2.5f);
        I_circle.setFillColor(sf::Color::Red);
        float y_i = -(c.I * 0.0026) + 575;
        I_circle.setPosition(n, y_i);
        m_window.draw(I_circle);

        sf::CircleShape R_circle(2.5f);
        R_circle.setFillColor(sf::Color::Blue);
        float y_r = -(c.R * 0.0026) + 575;
        R_circle.setPosition(n, y_r);
        m_window.draw(R_circle);

        ++i;
      }
    }

    {  // Legend
      sf::Font font;

      if (!font.loadFromFile("ZenDots-Regular.ttf")) {
        throw std::runtime_error{"Error\n"};
      }

      sf::Text text_S;
      text_S.setFont(font);
      text_S.setString("Susceptible");
      text_S.setFillColor(sf::Color::Black);
      text_S.setCharacterSize(16);
      text_S.setPosition(120.f, 20.f);
      sf::Text text_I;
      text_I.setFont(font);
      text_I.setString("Infectious");
      text_I.setFillColor(sf::Color::Black);
      text_I.setCharacterSize(16);
      text_I.setPosition(380.f, 20.f);
      sf::Text text_R;
      text_R.setFont(font);
      text_R.setString("Recovered");
      text_R.setFillColor(sf::Color::Black);
      text_R.setCharacterSize(16);
      text_R.setPosition(640.f, 20.f);

      sf::CircleShape legend_S(2.5f);
      legend_S.setFillColor(sf::Color::Green);
      legend_S.setPosition(100.f, 30.f);
      sf::CircleShape legend_I(2.5f);
      legend_I.setFillColor(sf::Color::Red);
      legend_I.setPosition(360.f, 30.f);
      sf::CircleShape legend_R(2.5f);
      legend_R.setFillColor(sf::Color::Blue);
      legend_R.setPosition(620.f, 30.f);

      m_window.draw(text_S);
      m_window.draw(text_I);
      m_window.draw(text_R);
      m_window.draw(legend_S);
      m_window.draw(legend_I);
      m_window.draw(legend_R);
 
    }
  m_window.display();
  }
}
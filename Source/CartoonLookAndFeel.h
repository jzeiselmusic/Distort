/*
  ==============================================================================

    CartoonLookAndFeel.h
    Created: 30 Dec 2024 7:49:30am
    Author:  Jacob Zeisel

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

class CartoonLookAndFeel : public juce::LookAndFeel_V4
{
public:
    CartoonLookAndFeel() {}
    void drawRotarySlider(juce::Graphics& g, int x, int y, int width, int height,
                          float sliderPosProportional, float rotaryStartAngle, float rotaryEndAngle,
                          juce::Slider& slider) override
    {
        // Background of the rotary slider (cartoon-style circle)
        auto radius = (float) juce::jmin(width / 2, height / 2) - 4.0f;
        auto centerX = (float) x + (float) width * 0.5f;
        auto centerY = (float) y + (float) height * 0.5f;
        auto rx = centerX - radius;
        auto ry = centerY - radius;
        auto rw = radius * 2.0f;

        // Draw a colorful cartoon-like base
        g.setColour(juce::Colours::lightblue);
        g.fillEllipse(rx, ry, fmax(0,rw), fmax(0,rw));

        // Draw the border
        g.setColour(juce::Colours::black);
        g.drawEllipse(rx, ry, fmax(0,rw), fmax(0,rw), 3.0f);

        // Draw the "pointer" or indicator
        auto angle = rotaryStartAngle + sliderPosProportional * (rotaryEndAngle - rotaryStartAngle);
        auto pointerLength = radius * 0.6f;
        auto pointerThickness = 4.0f;

        juce::Path pointerPath;
        pointerPath.addRectangle(-pointerThickness * 0.5f, -radius, pointerThickness, pointerLength);
        pointerPath.applyTransform(juce::AffineTransform::rotation(angle).translated(centerX, centerY));

        g.setColour(juce::Colours::black);
        g.fillPath(pointerPath);
    }
};

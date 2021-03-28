<p align="center">
  <img src="https://github.com/Shobhit2000/Posture.ai/blob/master/Dump/Frame%2013.png" width="1000" title="hover text">
</p>

## Inspiration
With more people working at home due to the pandemic, we felt empowered to improve healthcare at an individual level. Existing solutions for posture detection are expensive, lack cross-platform support, and often require additional device purchases. We sought to remedy these issues by creating Upright.

## What it does
Upright uses your laptop's camera to analyze and help you improve your posture. Register and calibrate the system in less than two minutes, and simply keep Upright open in the background and continue working. Upright will notify you if you begin to slouch so you can correct it. Upright also has the Upright companion iOS app to view your daily metrics.

Some notable features include:

Smart slouch detection with ML
Little overhead - get started in < 2 min
Native notifications on any platform
Progress tracking with an iOS companion app

## How we built it
We created Upright’s desktop app using Electron.js, an npm package used to develop cross-platform apps. We created the individual pages for the app using HTML, CSS, and client-side JavaScript. For the onboarding screens, users fill out an HTML form which signs them in using Firebase Authentication and uploads information such as their name and preferences to Firestore. This data is also persisted locally using NeDB, a local JavaScript database. The menu bar addition incorporates a camera through a MediaDevices web API, which gives us frames of the user’s posture. Using Tensorflow’s PoseNet model, we analyzed these frames to determine if the user is slouching and if so, by how much. The app sends a desktop notification to alert the user about their posture and also uploads this data to Firestore. Lastly, our SwiftUI-based iOS app pulls this data to display metrics and graphs for the user about their posture over time.

## Challenges we ran into
We faced difficulties when managing data throughout the platform, from the desktop app backend to the frontend pages to the iOS app. As this was our first time using Electron, our team spent a lot of time discovering ways to pass data safely and efficiently, discussing the pros and cons of different solutions. Another significant challenge was performing the machine learning on the video frames. The task of taking in a stream of camera frames and outputting them into slouching percentage values was quite demanding, but we were able to overcome several bugs and obstacles along the way to create the final product.

## Accomplishments that we're proud of
We’re proud that we’ve come up with a seamless and beautiful design that takes less than a minute to setup. The slouch detection model is also pretty accurate, something that we’re pretty proud of. Overall, we’ve built a robust system that we believe outperforms other solutions using just the webcamera of your computer, while also integrating features to track slouching data on your mobile device.

## What we learned
This project taught us how to combine multiple complicated moving pieces into one application. Specifically, we learned how to make a native desktop application with features like notifications built-in using Electron. We also learned how to connect our backend posture data with Firestore to relay information from our Electron application to our OS app. Lastly, we learned how to integrate a machine learning model in Tensorflow within our Electron application.

## What's next for Upright
The next step is improving the posture detection model with more training data, tailored for each user. While the posture detection model we currently use is pretty accurate, by using more custom-tailored training data, it would take Upright to the next level. Another step for Upright would be adding Android integration for our mobile app, which currently only supports iOS as of now.

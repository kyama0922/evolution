@echo off
cd %~d0
cd evolution-core
git pull

cd ../evolution-framework
git pull

cd ../evolution-graphic
git pull

cd ../evolution-input
git pull

cd ../evolution-network
git pull

cd ../evolution-sound
git pull

cd ../evolution-utility
git pull
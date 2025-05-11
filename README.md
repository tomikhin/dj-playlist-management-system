# DJ Playlist Management System

## Overview

A console-based C++ application designed for DJs to manage song playlists for events and festivals. This system allows for dynamic playlist management with preference-based song queuing, playback control, and history tracking using circular queue data structures.

## Features

### 1. Preference-Based Song Management

- Organizes songs into **three priority levels** (*VIP*, *Regular*, *Low*)
- Plays higher preference songs first, maintaining order within each preference level
- Automatically selects the next highest priority song when the current one finishes

### 2. Song Playback Control

- Play songs from the queue based on priority
- Skip specific time intervals of the currently playing song
- Replay the last played song from history
- Remove specific songs from any playlist by name

### 3. Playlist Visualization

- Display all songs in order of playback priority
- View history of previously played songs in chronological order
- Track remaining playback time for the current song

### 4. File-Based I/O

- Reads commands from **input.txt**
- Writes operation results to **output.txt**
- Supports batch processing of playlist operations

## Usage Instructions

- Adding a Song
`ADD [preference_type] [duration] [song_name]`

*preference_type*: 1 (VIP), 2 (Regular), 3 (Low)  
*duration*: Length of song in seconds  
*song_name*: Name of the song  

- Playing a Song
`PLAY`  
Begins playback of the highest priority song in the queue

- Skipping Part of a Song
`SKIP [seconds]`  
Skips forward by specified number of seconds in the current song

- Replaying Last Song
`REPLAY`  
Puts the last played song back at the front of its preference queue and plays it again

- Removing a Song
`REMOVE [song_name]`  
Removes the specified song from any playlist it's found in

- Showing Current Playlists
`SHOW`  
Displays all songs in all playlists, organized by preference level

- Viewing Playback History
`HISTORY`  
Shows the chronological list of all songs that have been played

## Implementation Details

- Uses circular queue data structures for efficient song management
- Separate queues for each preference level
- Additional queue for tracking playback history
- Time-based tracking system for current song progress

## Error Handling

The system validates operations and provides appropriate messages for:

- Attempting to play songs when playlists are empty
- Skipping when no song is currently playing
- Replaying when history is empty
- Removing a song that doesn't exist in any playlist

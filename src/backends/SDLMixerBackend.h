/*
 *  SDLMixerBackend.h
 *  openc2e
 *
 *  Created by Alyssa Milburn on Thu Oct 09 2008.
 *  Copyright (c) 2008 Alyssa Milburn. All rights reserved.
 *
 *  This library is free software; you can redistribute it and/or
 *  modify it under the terms of the GNU Lesser General Public
 *  License as published by the Free Software Foundation; either
 *  version 2 of the License, or (at your option) any later version.
 *
 *  This library is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 *  Lesser General Public License for more details.
 *
 */

#ifndef _SDLMIXERBACKEND_H
#define _SDLMIXERBACKEND_H

#include "SkeletonAudioBackend.h"
#include <memory>
#include <vector>

#include "SDL_mixer.h"

class SDLMixerBuffer {
protected:
	SDLMixerBuffer(Mix_Chunk *);

	friend class SDLMixerBackend;
	friend class SDLMixerSource;

	Mix_Chunk *buffer;

public:
	~SDLMixerBuffer();
	unsigned int length_ms() const; /* milliseconds */
	unsigned int length_samples() const;
};

typedef std::unique_ptr<SDLMixerBuffer> SDLMixerClip;

class SDLMixerSource : public SkeletonAudioSource {
protected:
	SDLMixerSource();
	
	friend class SDLMixerBackend;
	
	SDLMixerClip clip;
	AudioStream stream;
	int channel;

public:
	~SDLMixerSource();

	virtual SourceState getState() const;
	virtual void play();
	virtual void stop();
	virtual void fadeOut();
	virtual void setPos(float x, float y, float plane);
	virtual bool isLooping() const;
	virtual void setLooping(bool);
	virtual void setVolume(float v);
	virtual void setMute(bool);
	virtual void setFollowingView(bool);

	virtual AudioStream getStream() const {
		return stream;
	}
	virtual void setStream(const AudioStream &stream_) {
		stream = stream_;
	}
};

class SDLMixerBackend : public AudioBackend {
protected:
	bool muted;

	std::shared_ptr<AudioSource> bgm_source;
	std::vector<int16_t> bgm_render_buffer;
	static void mixer_callback(void *userdata, uint8_t *buffer, int num_bytes);

public:
	SDLMixerBackend();
	void init();
	void shutdown();

	void setViewpointCenter(float, float);
	void setMute(bool);
	bool isMuted() const { return muted; }
	std::shared_ptr<AudioSource> newSource();
	std::shared_ptr<AudioSource> loadClip(const std::string &);

	std::shared_ptr<AudioSource> getBGMSource();
};

#endif

/* vim: set noet: */

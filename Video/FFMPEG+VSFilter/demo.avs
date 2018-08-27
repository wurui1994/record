video=FFVideoSource(vPath).getResize(0).TextSub(assPath)
audio=FFAudioSource(vPath).AmplifydB(6,6)
final=video.AudioDub(audio)
return final
function Process( clip C )
{
  Return( C.AudioChannels == 6 ? c6_stereo( C ) : C )
}
function c6_stereo(clip a)
{
     fl = GetChannel(a, 1)
     fr = GetChannel(a, 2)
     fc = GetChannel(a, 3)
     lf = GetChannel(a, 4)
     sl = GetChannel(a, 5)
     sr = GetChannel(a, 6)
     fl_sl = MixAudio(fl, sl, 0.2929, 0.2929)
     fr_sr = MixAudio(fr, sr, 0.2929, 0.2929)
     fc_lf = MixAudio(fc, lf, 0.2071, 0.2071)
     l = MixAudio(fl_sl, fc_lf, 1.0, 1.0)
     r = MixAudio(fr_sr, fc_lf, 1.0, 1.0)
     return MergeChannels(l, r)
}
function getResize(video, ar){
	h = Float(Video.Height)
	w = Float(Video.Width)
	ar = ar > 0 ? ar : w/h
	ow = w < 1280 ? w : 1280
	oh = mod2(ow / ar)
	
	oh = oh < 720 ? oh : 720
	ow = oh!=720 ? ow : mod2(oh * ar)
	
	left = trunc(Float(1280-ow)/2)
	top = trunc(Float(720-oh)/2)
	right = trunc((1280-ow)-left)
	bottom = trunc((720-oh)-top)
	
	return video.LanczosResize(ow, oh).addBorders(left,top,right,bottom).LanczosResize(1280, 720)
}

function mod2(x){
	x = (Floor(x) % 2 == 0) ? Floor(x) : (Floor(x) + 1)
	return x
}

function trunc(x){
	x = (mod2(x) >= 10) ? mod2(x) : 0
	return x
}
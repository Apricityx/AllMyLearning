public class Player {
    private final Decoder[] decoders = {new MP3Decoder(), new WAVDecoder()};
    public void play(String path) {
        for(Decoder d : decoders) {
            if(d.canDecode(path)) {
                d.decode(path);
            }
        }
    }
}
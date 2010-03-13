CC=clang++
CFLAGS=-Os -IPlugins -I. -ISystem

all: libxnet.a

libxnet.a: Peer.o DataSerialiser.o DataUnserialiser.o Message.o Plugin.o Plugins/Ordering.o Plugins/Reliability.o Plugins/SimulateLag.o Plugins/Splitting.o
	ar -c -q -s $@ $^

System/SocketProvider.o: System/SocketProvider.cpp System/SocketProvider.h
	$(CC) -c $(CFLAGS) -o $@ $<

Peer.o: Peer.cpp XNet.h DataUnserialiser.h DataSerialiser.h System/SocketProvider.h
	$(CC) -c $(CFLAGS) -o $@ $<

DataSerialiser.o: DataSerialiser.cpp DataSerialiser.h
	$(CC) -c $(CFLAGS) -o $@ $<

DataUnserialiser.o: DataUnserialiser.cpp DataUnserialiser.h
	$(CC) -c $(CFLAGS) -o $@ $<

Message.o: Message.cpp XNet.h DataUnserialiser.h DataSerialiser.h System/SocketProvider.h
	$(CC) -c $(CFLAGS) -o $@ $<

Plugin.o: Plugin.cpp XNet.h DataUnserialiser.h DataSerialiser.h System/SocketProvider.h
	$(CC) -c $(CFLAGS) -o $@ $<

Plugins/Ordering.o: Plugins/Ordering.cpp Plugins/Ordering.h XNet.h DataUnserialiser.h DataSerialiser.h System/SocketProvider.h
	$(CC) -c $(CFLAGS) -o $@ $<

Plugins/Reliability.o: Plugins/Reliability.cpp Plugins/Reliability.h XNet.h DataUnserialiser.h DataSerialiser.h System/SocketProvider.h
	$(CC) -c $(CFLAGS) -o $@ $<

Plugins/SimulateLag.o: Plugins/SimulateLag.cpp Plugins/SimulateLag.h XNet.h DataUnserialiser.h DataSerialiser.h System/SocketProvider.h
	$(CC) -c $(CFLAGS) -o $@ $<

Plugins/Splitting.o: Plugins/Splitting.cpp Plugins/Splitting.h XNet.h DataUnserialiser.h DataSerialiser.h System/SocketProvider.h
	$(CC) -c $(CFLAGS) -o $@ $<

clean:
	rm -f *.o Plugins/*.o libxnet.a

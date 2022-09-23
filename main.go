package main

import (
	"fmt"
	"net"
	"os"
	"time"
)

var (
	deadline         = time.Millisecond * 1000
	maxTime          = time.Millisecond * 0
	minTime          = time.Millisecond * 0
	txCnt            = 0
	txErr            = 0
	rxCnt            = 0
	rxErr            = 0
	exitOnTxErr      = true
	exitOnRxErr      = true
	waitBetweenSends = time.Millisecond * 200
	txJitter         = time.Millisecond * 1
	histoCluster     = time.Millisecond * 5
	txLenByte        = 1024
	rxLenByte        = 1024
	overallTime      = time.Millisecond * 0
)

func main() {

	arguments := os.Args
	if len(arguments) == 1 {
		fmt.Println("Provide the UDP server <host>:<port> as argument")
		return
	}
	CONNECT := arguments[1]

	s, err := net.ResolveUDPAddr("udp4", CONNECT)
	c, err := net.DialUDP("udp4", nil, s)

	if err != nil {
		fmt.Println(err)
		return
	}

	defer c.Close()

	data := make([]byte, txLenByte)
	for {
		_, err = c.Write(data)
		tStart := time.Now()

		if err != nil {
			txErr++

			fmt.Println(err)
			if exitOnTxErr {
				// TODO Print stats
				return
			}
		} else {
			txCnt++
		}

		buffer := make([]byte, rxLenByte)

		_, _, err := c.ReadFromUDP(buffer)
		if err != nil {
			rxErr++

			fmt.Println(err)
			if exitOnRxErr {
				return
			}
		} else {
			rxCnt++
		}

		tEnd := time.Now()
		tDelta := tEnd.Sub(tStart)

		overallTime = overallTime + tDelta

		if tDelta > maxTime {
			maxTime = tDelta
			fmt.Println("New max time: ", maxTime)
		}

		fmt.Println("Ovr:", overallTime.Milliseconds(), "Avg: ", float64(overallTime.Milliseconds())/float64(rxCnt), "Max: ", maxTime)

		time.Sleep(waitBetweenSends)
	}
}

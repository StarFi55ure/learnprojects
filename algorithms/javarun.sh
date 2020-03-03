#!/bin/bash

mvn compile exec:java -Dexec.mainClass=org.dyndns.ratel.$1 < $2

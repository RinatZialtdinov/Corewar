.name		"Mikael Blomkvist"
.comment	"Hans-Erik Wennerstrom is a liar!"

# Executable code

ld	%1,			r2	# Store operator code of live
ld	%655250,	r4	# Store zjmp with arguments
ld	%786932,	r5	# Store fork with arguments
ld	%655275,	r6	# Store zjmp with arguments
ld	%0,			r16	# Change carry to 1

sti	r1, %:sweden,		%1
sti	r1, %:uppsala,		%1
sti	r1, %:hedestad,		%1
sti	r1, %:malmo,		%1
sti	r1, %:stockholm,	%1
sti	r1, %:slussen,		%1
sti	r1, %:gotgatan,		%1
sti	r1, %:mosebacke,	%1
sti	r1, %:bellmansgatan,%1
sti	r1, %:lundagatan,	%1
sti	r1, %:hedeby,		%1
sti	r1, %:gothenburg,	%1

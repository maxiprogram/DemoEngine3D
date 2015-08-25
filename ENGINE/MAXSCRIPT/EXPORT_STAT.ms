--CONVERT
function convert obj &masver &mastex &masface &masnorm=
(
	for i=1 to obj.numFaces do
	(
		face=getFace obj i
		tvf=getTVFace obj i
		ver=getVert obj face.x
		--n=getNormal obj face.x
		n=meshop.getFaceRNormals obj i
		append masver ver
		append masnorm n[1]
		--texture X coordinat
		tv=getTVert obj tvf.x
		append mastex tv
		--end texture X coordinat
		ver=getVert obj face.y
		--n=getNormal obj face.y
		append masver ver
		append masnorm n[2]
		--texture Y coordinat
		tv=getTVert obj tvf.y
		append mastex tv
		--end texture Y coordinat
		ver=getVert obj face.z
		--n=getNormal obj face.z
		append masver ver
		append masnorm n[3]
		--texture Z coordinat
		tv=getTVert obj tvf.z
		append mastex tv
	)
	
		
	i=1
	ii=0
	while (i<masver.count) do
	(
		j=i+1
		if (masver[i]!=undefined) then
		(
			if (masface[i]==undefined) then
				masface[i]=i-ii
			while (j<=masver.count) do
			(
				if (masver[i]==masver[j] and mastex[i]==mastex[j] and masnorm[i]==masnorm[j]) then
				(
					masver[j]=undefined
					masnorm[j]=undefined
					mastex[j]=undefined
					masface[j]=i-ii
				)
				j=j+1
			)
		)else
		ii=ii+1
		i=i+1
	)
		
	i=1
	while (i<=masver.count) do
	(
		bl=0
		if (masver[i]==undefined) then
		(
			deleteItem masver i
			deleteItem masnorm i
			deleteItem mastex i
			bl=1
		)
		if (bl==0) then
			i=i+1
	)
)

---------------------------------------------------------------
--BEGIN
arr=#()
file=fopen "d:\\demo.stat" "wb"

for obj in objects do
(
	if ((classOf obj)!=BoneGeometry) and ((classOf obj)!=Biped_Object) and (canConvertTo obj TriMeshGeometry) then
	(
		mb=convertToMesh obj
		append arr obj
	)	
)

writeLong file arr.count
format "name=%\n" arr[1].name
writeString file arr[1].name

icountface=0
unionface=#()
unionvertex=#()
uniontexture=#()
unionnormal=#()
attribute=#()
iattr=0

for i=1 to arr.count do
(
	masv=#()
	masn=#()
	mast=#()
	masf=#()
	convert arr[i] masv mast masf masn
	--format "facedoooo=% verdoo=%\n" masf.count masv.count
	for icf=1 to masf.count do
	(
		buf=masf[icf]+icountface
		append unionface buf
		append attribute iattr
	)
	
	for icv=1 to masv.count do
	(
		append unionvertex masv[i]
		append uniontexture mast[i]
		append unionnormal masn[i]
	)

	icountface=(icountface+masv.count)
	iattr=iattr+1
)

buf=unionface.count/3
writeLong file buf --Кол-во полигонов
format "Count Face=%\n" buf

for i=1 to unionface.count do
(
	buf=unionface[i]-1
	writeLong file buf
)

for i=1 to attribute.count do
	writeLong file attribute[i]
	
for i=1 to arr.count do
(
	if (arr[i].material!=undefined) then
	(
		writeByte file arr[i].material.ambient.a
		writeByte file arr[i].material.ambient.r
		writeByte file arr[i].material.ambient.g
		writeByte file arr[i].material.ambient.b
		writeByte file arr[i].material.diffuse.a
		writeByte file arr[i].material.diffuse.r
		writeByte file arr[i].material.diffuse.g
		writeByte file arr[i].material.diffuse.b
		writeByte file arr[i].material.specular.a
		writeByte file arr[i].material.specular.r
		writeByte file arr[i].material.specular.g
		writeByte file arr[i].material.specular.b
		b=arr[i].material.maps[2]
		if (b!=undefined) then
		(
			str=arr[i].material.maps[2].filename
			c=findstring str "\\"
			while c!=undefined do
			(
				str=replace str 1 c ""
				c=findstring str "\\"
			)
			writeString file str
			print str
		)else writeByte file 0
			--path texture
	)else
	(
		writeByte file 255
		writeByte file 255
		writeByte file 255
		writeByte file 255
		writeByte file 255
		writeByte file 255
		writeByte file 255
		writeByte file 255
		writeByte file 255
		writeByte file 255
		writeByte file 255
		writeByte file 255
		writeByte file 0
	)--material	
)

countvertex=0
for i=1 to arr.count do
(
	masv=#()
	masn=#()
	mast=#()
	masf=#()
	convert arr[i] masv mast masf masn
	countvertex=countvertex+masv.count
)
writeLong file countvertex --Кол-во вершин
format "Count Vertex=%\n" countvertex

for i=1 to arr.count do
	(
		masv=#()
		masn=#()
		mast=#()
		masf=#()
		convert arr[i] masv mast masf masn
		
		for iv=1 to masv.count do
		(
			writeFloat file masv[iv].x
			writeFloat file masv[iv].z
			writeFloat file masv[iv].y
			writeFloat file masn[iv].x
			writeFloat file masn[iv].z
			writeFloat file masn[iv].y	
			--texture coordinat
			writeFloat file mast[iv].x
			writeFloat file (1-mast[iv].y)
			--format "x=% y=% z=%\n" vertex.x vertex.y vertex.z
		)--end for vertex
	)

fclose file
format "------------GOOD------------\n"

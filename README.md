# SFMLPlayground
Just messing around with SFML. Note that this repo uses SFML 2.5.1 (check out https://www.sfml-dev.org/download.php for the latest version), and expects it to be in `C:\SFML-2.5.1`. If you're using a newer version, you'll need to update the VS project properties and copy new DLLs into the project folder.

This project is using a hard-coded map with a hard-coded BSP tree, here's a view of the map's sectors before parsing:

![PXL_20230128_200857621](https://user-images.githubusercontent.com/2153171/215298001-a72d94dd-efe5-4935-9c34-bbb89800e88b.jpg)

Here are the map's sub-sectors based on the BSP tree:

![PXL_20230128_210540841](https://user-images.githubusercontent.com/2153171/215298034-b9ac10a4-d02f-4874-859f-18de6639ddd8.jpg)

And here's the BSP tree itself:

![PXL_20230129_002146637](https://user-images.githubusercontent.com/2153171/215298049-35518af8-bf46-4855-a7bf-c86e5c6c4cc4.jpg)

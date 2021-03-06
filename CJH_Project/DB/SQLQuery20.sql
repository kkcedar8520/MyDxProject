USE [KGCA37]
GO
/****** Object:  StoredProcedure [dbo].[CreateAccountUser]    Script Date: 01/09/2020 16:37:29 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO

ALTER PROCEDURE [dbo].[CreateAccountUser]
	@UID NCHAR(10),@UPS NCHAR(10),@RETURN int OUTPUT
AS
BEGIN TRY
BEGIN
	DECLARE @ret NCHAR(10);
	SELECT @ret=USERID from USERLIST
		WHERE USERID=@UID;
	IF(@ret <>N'')
	BEGIN
		SET @ret=3;
		RETURN 3;
	END
		
	INSERT INTO USERLIST(USERID,USERPS) VALUES(@UID,@UPS);
	
	SET @ret =1;
	return 1;
END
END TRY
--ERROR
BEGIN CATCH
	SET @ret=9;
	RETURN 9;
END CATCH
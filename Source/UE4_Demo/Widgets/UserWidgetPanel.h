// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "../Action/IActionNode.h"
#include "../Action/ActionWraper.h"
#include "Delegate.h"
#include "UserWidgetPanel.generated.h"

UENUM()
enum class EPanelShowType
{
	E_PANEL_SHOW_NORMAL,			
	E_PANEL_SHOW_PUSH,				
	E_PANEL_SHOW_APPEND,
	E_PANEL_SHOW_REPLACE,
	E_PANEL_SHOW_RESTORE,
};

UENUM()
enum class EPanelHideType
{
	E_PANEL_HIDE_NORMAL,
	E_PANEL_HIDE_PUSH,
	E_PANEL_HIDE_CLOSE,
};

/**
 * 
 */
UCLASS()
class UE4_DEMO_API UUserWidgetPanel : public UUserWidget, public IActionNode
{
	GENERATED_BODY()
	friend class UUserWidgetsManager;
public:
	DECLARE_DYNAMIC_DELEGATE_TwoParams(FUserPanelDelegate, UUserWidgetPanel*, Panel, uint8, type);
protected:
	UPROPERTY(EditAnywhere, Category = "Panel Property")
	FString m_selFString;
	UPROPERTY(EditAnywhere, Category = "Panel Property")
	FString m_associatedName;
	UPROPERTY(EditAnywhere, Category = "Panel Property")
	int32	m_panelGroup;
	UPROPERTY(EditAnywhere, Category = "Panel Property")
	int32	m_zOrder;
	UPROPERTY(BlueprintReadWrite, Category = "Panel Property")
	uint8	m_showType;
	UPROPERTY(BlueprintReadWrite, Category = "Panel Property")
	bool	m_bIsShowed;
	UPROPERTY(EditAnywhere, Category = "Panel Property")
	FVector2D	m_showPoint;
	UPROPERTY(EditAnywhere, Category = "Panel Property")
	FVector2D	m_initPoint;
	UPROPERTY(EditAnywhere, Category = "Panel Property")
	FVector2D	m_initScale;

public:
	UPROPERTY(EditAnywhere, Category = "Panel Event")
	FUserPanelDelegate OnShowDelegate;
	UPROPERTY(EditAnywhere, Category = "Panel Event")
	FUserPanelDelegate OnHideDelegate;
public:
	virtual void PostLoad() override;
	virtual void FinishDestroy() override;

	//----------------------------------------------
	// extra event
	UFUNCTION(BlueprintNativeEvent, Category = "Panel")
	void onPostLoad();
	virtual void onPostLoad_Implementation();

	UFUNCTION(BlueprintNativeEvent, Category = "Panel")
	void onDestory();
	virtual void onDestory_Implementation();

	//----------------------------------------------------
	UFUNCTION(BlueprintNativeEvent, Category = "Panel")
	void Show(uint8 showType);
	virtual void Show_Implementation(uint8 showType);
	UFUNCTION(BlueprintNativeEvent, Category = "Panel")
	void ShowByAssociated(uint8 showType, const FString& associatedName);
	virtual void ShowByAssociated_Implementation(uint8 showType, const FString& associatedName);
	UFUNCTION(BlueprintNativeEvent, Category = "Panel")
	void Hide(uint8 hideType);
	virtual void Hide_Implementation(uint8 hideType);

protected:
	virtual void InnerShow(uint8 showType, const FString& associatedName);
	UFUNCTION(BlueprintCallable, Category = "Panel")
	void onShow( uint8 showType );
	UFUNCTION(BlueprintCallable, Category = "Panel")
	void onHide(uint8 hideType);

private:
	void onFinishShow(void* pContext);
	void onFinishHide(void* pContext);

public:
	//------------------------------------------
	// helper
	//------------------------------------------
	UFUNCTION(BlueprintCallable, Category = "Panel")
	void setPanelName( const FString& name );
	UFUNCTION(BlueprintPure, Category = "Panel")
	const FString& getPanelName() const;
	UFUNCTION(BlueprintPure, Category = "Panel")
	const FString& getAssociatedName() const;
	UFUNCTION(BlueprintPure, Category = "Panel")
	int32 getCatalog() const;
	UFUNCTION(BlueprintPure, Category = "Panel")
	uint8 getShowType() const;
	UFUNCTION(BlueprintPure, Category = "Panel")
	bool isShowed() const;
	//------------------------------------------
	// IActionNode
	//-------------------------------------------
	UFUNCTION(BlueprintCallable, Category = "Action")
	virtual FVector getLocation() const override;
	UFUNCTION(BlueprintCallable, Category = "Action")
	virtual void setLocation(const FVector& location) override;
	UFUNCTION(BlueprintCallable, Category = "Action")
	virtual FVector	getScale() const override;
	UFUNCTION(BlueprintCallable, Category = "Action")
	virtual void setScale(FVector s) override;
	virtual void runAction(const std::shared_ptr<FAction>& action) override;
	virtual void stopAction(const std::shared_ptr<FAction>& action) override;
	UFUNCTION(BlueprintCallable, Category = "Action")
	virtual void stopAllActions() override;
	virtual void pauseAction(const std::shared_ptr<FAction>& action) override;
	UFUNCTION(BlueprintCallable, Category = "Action")
	virtual void pauseAllActions() override;
	virtual void resumeAction(const std::shared_ptr<FAction>& action) override;
	UFUNCTION(BlueprintCallable, Category = "Action")
	virtual void resumeAllActions() override;

	//--------------------------------------
	UFUNCTION(BlueprintCallable, Category = "Action")
    void runAction(UActionWraper* action);
	UFUNCTION(BlueprintCallable, Category = "Action")
	void stopAction(UActionWraper* action);
	UFUNCTION(BlueprintCallable, Category = "Action")
	void pauseAction(UActionWraper* action);
	UFUNCTION(BlueprintCallable, Category = "Action")
	void resumeAction(UActionWraper* action);
};

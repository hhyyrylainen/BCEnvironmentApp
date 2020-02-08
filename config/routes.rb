# frozen_string_literal: true

Rails.application.routes.draw do
  get 'profile', to: 'profile#index'
  get 'badges', to: 'badges#index'
  get 'leaderboards', to: 'leaderboards#index'
  devise_for :users
  get 'home/index'
  # For details on the DSL available within this file, see https://guides.rubyonrails.org/routing.html

  authenticate :user, ->(user) { user.admin? } do
    mount Sidekiq::Web => '/sidekiq'
  end

  resources :users
  resources :tasks

  root 'home#index'
end
